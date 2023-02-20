<script>
    import Highcharts from 'highcharts'
    import Data from "highcharts/modules/data";
    import { afterUpdate } from 'svelte';

    let completion = 0;
    Data(Highcharts);

    afterUpdate(() => {
        async function handle() {
            const res = await fetch('https://raw.githubusercontent.com/FluentCoding/MeleeDecompProgressCalc/master/result.csv')
            const lines = (await res.text()).split(/\r\n|\n|\r/);
            let codePct = [];
            let dataPct = [];

            for (var line of lines) {
                const values = line.split(',')

                if (values.length !== 6)
                    continue;

                codePct.push({
                    x: parseFloat(values[1]) * 1000,
                    y: parseFloat(values[2]) * 100 /* Percent */,
                    commitId: values[0],
                    trophies: values[4],
                    events: values[5]
                })
                dataPct.push({
                    x: parseFloat(values[1] * 1000),
                    y: parseFloat(values[3] * 100 /* Percent */),
                    commitId: values[0],
                    trophies: values[4],
                    events: values[5]
                })
            }

            completion = codePct[codePct.length - 1].y
            chart = Highcharts.chart('container', {
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
                    formatter: function() {
                        return "<b>" + (this.series.name === "Code percentage completed" ? "Code" : "Data") + " Percentage completed:</b> " + getPercentage(this.point.y) +
                            "<br><b>Trophies collected</b>: " + this.point.trophies + "/290" +
                            "<br><b>Event Matches completed:</b> " + this.point.events + "/51" +
                            "<br><br><b>Commit ID:</b> <a target=\"_blank\"href=\"https://github.com/doldecomp/melee/commit/" + this.point.commitId + "\">" + this.point.commitId + "</a>" +
                            "<br><b>Commit Date:</b> " + new Date(this.point.x).toLocaleString()
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
                        format: '{value}%',
                        style: {
                            color: 'white'
                        }
                    },
                    title: false
                },
                series: [{
                    name: "Code percentage completed",
                    data: codePct,
                    lineWidth: 4
                }, {
                    name: "Data percentage completed",
                    data: dataPct,
                    lineWidth: 4,
                    color: 'green'
                }],
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
                },
            });

            return codePct[codePct.length - 1].y;
        }

        handle().then((val) => completion = val);
    })

    function getPercentage(value) {
        return value + "%";
    }
</script>

<div style="width: 100%; display: flex; justify-content: center;">
    <div id="progressbar">
        <div style={"width: " + getPercentage(completion)} />
    </div>
</div>
<div class="title">{getPercentage(Math.floor(completion * 100) / 100)} complete!</div>
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

    #progressbar>div {
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
