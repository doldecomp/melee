<script lang="ts">
    import Highcharts from 'highcharts';
    import Data from 'highcharts/modules/data';
    import Accessibility from 'highcharts/modules/accessibility';
    import { afterUpdate } from 'svelte';
    import type Progress from '../Progress';
    import progressJson from '$lib/extern/progress.json';
    Accessibility(Highcharts);

    type Point = Partial<Highcharts.Point>;
    type Points = Array<Point>;

    const progress = progressJson as Progress;
    const EVENT_COUNT = 51;
    const TROPHY_COUNT = 293;

    function formatPercent(value: number): string {
        return `${Math.round(value * 100) / 100}%`;
    }

    let completion = 0;
    Data(Highcharts);

    afterUpdate(() => {
        async function handle() {
            const codePct: Points = [];
            const dataPct: Points = [];

            for (const [_, project] of Object.entries(progress)) {
                for (const [_, version] of Object.entries(project)) {
                    for (const commit of version.dol) {
                        const measures = commit.measures;
                        const codeValue = measures.code / measures['code/total'];
                        const dataValue = measures.data / measures['data/total'];
                        const codePercent = codeValue * 100;
                        const dataPercent = dataValue * 100;
                        const trophies = Math.floor(TROPHY_COUNT * codeValue);
                        const events = Math.floor(EVENT_COUNT * dataValue);
                        const x = commit.timestamp * 1000;
                        const commitId = commit.git_hash;

                        completion = Math.max(completion, codePercent);

                        codePct.push({
                            x,
                            y: codePercent,
                            options: {
                                custom: {
                                    commitId,
                                    trophies,
                                    events
                                }
                            }
                        });

                        dataPct.push({
                            x,
                            y: dataPercent,
                            options: {
                                custom: {
                                    commitId,
                                    trophies,
                                    events
                                }
                            }
                        });
                    }
                }
            }

            function comparePoint(a: Point, b: Point) {
                return (a?.x ?? 0) - (b?.x ?? 0);
            }

            codePct.sort(comparePoint);
            dataPct.sort(comparePoint);

            Highcharts.chart(
                'container',
                {
                    chart: {
                        zoomType: 'x',
                        panning: true,
                        panKey: 'shift',
                        backgroundColor: 'transparent',
                        style: {
                            fontFamily: 'A-OTF Folk Pro',
                            color: 'white'
                        }
                    },
                    title: {
                        text: 'Melee Decompilation Progress History',
                        style: {
                            color: 'white'
                        }
                    },
                    subtitle: {
                        text: 'SSBM 1.02 NTSC (' + codePct.length + ' recorded commits)',
                        style: {
                            color: 'lightgray'
                        }
                    },
                    tooltip: {
                        valueDecimals: 2,
                        style: {
                            pointerEvents: 'auto'
                        },
                        useHTML: true,
                        formatter: function () {
                            const custom = this.point.options.custom;
                            if (custom === undefined) {
                                throw new Error('No custom data');
                            }

                            const y = this.point.y;
                            if (y === undefined) {
                                throw new Error('No y value');
                            }

                            const shortName = this.series.options.custom?.shortName;
                            if (shortName === undefined) {
                                throw new Error('No short name');
                            }

                            const { trophies, events, commitId } = custom;
                            const yPercent = formatPercent(y);
                            const shortCommit = commitId.substring(0, 7).toLowerCase();
                            const commitUrl = `https://github.com/doldecomp/melee/commit/${commitId}`;
                            const date = new Date(this.point.x).toLocaleString();

                            return `<strong>${shortName} Percentage completed:</strong> ${yPercent} <br>
<strong>Trophies collected</strong>: ${trophies}/${TROPHY_COUNT} <br>
<strong>Event Matches completed:</strong> ${events}/${EVENT_COUNT} <br>
<br>
<strong>Commit ID:</strong>
<code>
  <a target="_blank" href="${commitUrl}">${shortCommit}</a>
</code>
<br>
<strong>Commit Date:</strong> ${date}`;
                        }
                    },
                    xAxis: {
                        type: 'datetime',
                        labels: {
                            style: {
                                color: 'white'
                            }
                        }
                    },
                    yAxis: {
                        labels: {
                            format: '{value:.2f}%',
                            style: {
                                color: 'white'
                            }
                        },
                        title: false
                    },
                    series: [
                        {
                            name: 'Code percentage completed',
                            data: codePct,
                            lineWidth: 4,
                            custom: {
                                shortName: 'Code'
                            }
                        },
                        {
                            name: 'Data percentage completed',
                            data: dataPct,
                            lineWidth: 4,
                            color: 'green',
                            custom: {
                                shortName: 'Data'
                            }
                        }
                    ],
                    legend: {
                        itemStyle: {
                            color: 'white'
                        }
                    },
                    plotOptions: {
                        series: {
                            states: {
                                inactive: {
                                    opacity: 0.8,
                                    lineWidth: 2
                                }
                            }
                        }
                    },
                    credits: {
                        enabled: false
                    }
                },
                undefined
            );
        }

        handle();
    });
</script>

<div style="width: 100%; display: flex; justify-content: center;">
    <div id="progressbar">
        <div style={'width: ' + formatPercent(completion)} />
    </div>
</div>
<div class="title">{formatPercent(completion)} complete!</div>
<div id="container" class="container" />

<style>
    .title {
        color: white;
        font-size: 32px;
    }

    .container {
        display: block;
        min-height: 400px;
        min-width: 800px;
        margin: 0 auto;
        margin-top: 50px;

        border: 4px solid orange;
        box-shadow: 0 0 10px orange;
        border-radius: 12px;
        padding: 10px;
    }

    #progressbar {
        width: 50%;
        text-align: center;
        background-color: gray;
        border-radius: 13px;
        /* (height of inner div) / 2 + padding */
        padding: 3px;
    }

    #progressbar > div {
        background-color: yellow;
        height: 20px;
        border-radius: 10px;
    }

    @media (max-width: 1300px) {
        .container {
            width: 80vw;
        }
    }
</style>
