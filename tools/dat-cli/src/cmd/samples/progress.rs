//! Objdiff's version-2 report schema, using archive data rather than only
//! the selected samples as the denominator. Relocation differences are
//! included in each sample's score by `diff_unit`.

use super::UnitMatch;
use serde::Serialize;
use serde_json::{Value, json};

#[derive(Clone, Default, Serialize)]
struct Measures {
    total_data: u64,
    matched_data: u64,
    matched_data_percent: f64,
    fuzzy_match_percent: f64,
    complete_data: u64,
    complete_data_percent: f64,
    total_units: u32,
    complete_units: u32,
    #[serde(skip)]
    fuzzy_data: f64,
}

impl Measures {
    fn add(&mut self, other: &Self) {
        self.total_data += other.total_data;
        self.matched_data += other.matched_data;
        self.complete_data += other.complete_data;
        self.total_units += other.total_units;
        self.complete_units += other.complete_units;
        self.fuzzy_data += other.fuzzy_data;
        self.finish();
    }

    fn finish(&mut self) {
        let percent = |bytes: f64| match self.total_data {
            0 => 100.0,
            n => bytes * 100.0 / n as f64,
        };
        self.matched_data_percent = percent(self.matched_data as f64);
        self.complete_data_percent = percent(self.complete_data as f64);
        self.fuzzy_match_percent = percent(self.fuzzy_data);
    }
}

pub(super) fn report(units: &[UnitMatch]) -> Value {
    let mut total = Measures::default();
    let units: Vec<_> = units
        .iter()
        .map(|unit| {
            let mut measures = Measures {
                total_data: unit.measures.total_bytes,
                // Inferred non-sample pieces come from the walk. Only
                // fully matching C samples earn additional matched bytes;
                // partial scores contribute to fuzzy progress alone.
                matched_data: unit.inferred_bytes
                    + unit
                        .samples
                        .iter()
                        .filter(|s| s.match_percent >= 100.0)
                        .map(|s| s.size)
                        .sum::<u64>(),
                fuzzy_data: unit.measures.covered_bytes,
                complete_data: if unit.complete {
                    unit.measures.total_bytes
                } else {
                    0
                },
                total_units: 1,
                complete_units: u32::from(unit.complete),
                ..Default::default()
            };
            measures.finish();
            total.add(&measures);
            json!({
                "name": unit.name,
                "measures": measures,
                "metadata": {
                    "complete": unit.complete,
                    "progress_categories": ["dat"],
                    "auto_generated": false,
                },
            })
        })
        .collect();
    total.finish();
    json!({
        "version": 2,
        "measures": total,
        "units": units,
        "categories": [{
            "id": "dat",
            "name": "Dat Samples",
            "measures": total,
        }],
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::cmd::samples::{MatchMeasures, SampleMatch};

    fn unit(
        bytes: u64,
        inferred: u64,
        complete: bool,
        scores: &[(u64, f64)],
    ) -> UnitMatch {
        let samples: Vec<_> = scores
            .iter()
            .map(|&(size, match_percent)| SampleMatch {
                name: "sample".into(),
                size,
                match_percent,
            })
            .collect();
        let mut measures = MatchMeasures {
            total_bytes: bytes,
            covered_bytes: inferred as f64,
            ..Default::default()
        };
        for sample in &samples {
            measures.add(sample);
        }
        UnitMatch {
            name: "Mn/archive".into(),
            measures,
            samples,
            inferred_bytes: inferred,
            complete,
            extra: Vec::new(),
        }
    }

    #[test]
    fn whole_archives_and_fully_matching_samples() {
        let report = report(&[
            unit(100, 40, false, &[(10, 100.0), (20, 50.0), (10, 0.0)]),
            unit(60, 40, true, &[(20, 100.0)]),
        ]);
        let total = &report["measures"];
        assert_eq!(report["version"], 2);
        assert_eq!(total["total_data"], 160);
        assert_eq!(total["matched_data"], 110);
        assert_eq!(total["matched_data_percent"], 68.75);
        assert_eq!(total["fuzzy_match_percent"], 75.0);
        assert_eq!(total["complete_data"], 60);
        assert_eq!(total["complete_data_percent"], 37.5);
        assert_eq!(total["total_units"], 2);
        assert_eq!(total["complete_units"], 1);
        assert_eq!(report["categories"][0]["measures"], *total);
        assert_eq!(report["units"][0]["measures"]["matched_data"], 50);
        assert_eq!(report["units"][0]["metadata"]["complete"], false);
        assert_eq!(report["units"][1]["metadata"]["complete"], true);
    }

    #[test]
    fn empty_report_has_finite_percentages() {
        let empty = report(&[]);
        assert_eq!(empty["measures"]["total_units"], 0);
        assert_eq!(empty["measures"]["matched_data_percent"], 100.0);
        assert_eq!(empty["measures"]["fuzzy_match_percent"], 100.0);
        let zero = report(&[unit(0, 0, false, &[])]);
        assert_eq!(zero["measures"]["total_units"], 1);
        assert_eq!(zero["measures"]["complete_units"], 0);
        assert_eq!(zero["measures"]["matched_data_percent"], 100.0);
    }
}
