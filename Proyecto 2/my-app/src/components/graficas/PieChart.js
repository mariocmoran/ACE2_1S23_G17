import Chart from 'chart.js';
import React, { useRef, useEffect } from 'react';

function PieChart(props){
    const chartRef = useRef();
    useEffect(() => {
        const myChartRef = chartRef.current.getContext('2d');
        new Chart(myChartRef, {
            type: 'pie',
            data: {
                labels: ['Humedad', 'NN'],
                datasets: [
                    {
                        data: [props.data, 100-props.data],
                        backgroundColor: ['#AED6F1'],
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
                tooltips: {
                    callbacks: {
                        label: function (tooltipItem, data) {
                            var value = data.datasets[0].data[tooltipItem.index];
                            return value.toString() + "%";
                        }
                    }
                },
                // otras opciones de la gráfica
            }
        });
    }, [props.data]);
    return(
        <div>
            <canvas id="myChart" ref={chartRef} style={{ margin: "auto", height: "20vh" }} />
        </div>
    );
}

export default PieChart