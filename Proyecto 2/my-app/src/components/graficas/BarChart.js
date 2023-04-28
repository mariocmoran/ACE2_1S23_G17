import Chart from 'chart.js';
import React, { useRef, useEffect } from 'react';

function BarChart(props) {
    const chartRef = useRef();
    useEffect(() => {
        const myChartRef = chartRef.current.getContext('2d');
        new Chart(myChartRef, {
            type: 'bar',
            data: {
                labels: [props.name],
                datasets: [
                    {
                        data: props.data,
                        backgroundColor: ['#C0392B'],
                    },
                ],
            },
            options: {
                scales: {
                    yAxes: {
                        ticks: {
                            beginAtZero: true,
                        },
                    }
                },
                legend: {
                    display: false,
                },
                // otras opciones de la gráfica
            }
        });
    }, [props.name, props.data]);

    return (
        <div>
            <canvas id="myChart" ref={chartRef} style={{ margin: "auto", height: "20vh" }} />
        </div>
    );
}

export default BarChart