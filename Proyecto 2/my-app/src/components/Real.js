
import BarChart from "./graficas/BarChart";
import PieChart from "./graficas/PieChart";
import React, { useRef, useEffect, useState } from 'react';

function useInterval(callback, delay) {
    const savedCallback = useRef();

    // Recuerda la última función de callback.
    useEffect(() => {
        savedCallback.current = callback;
    }, [callback]);

    // Configura el intervalo.
    useEffect(() => {
        function tick() {
            savedCallback.current();
        }

        if (delay !== null) {
            let id = setInterval(tick, delay);
            return () => clearInterval(id);
        }
    }, [delay]);
}

function Real() {
    const [dataExterna, setDataExterna] = useState([0])
    const [dataInterna, setDataInterna] = useState([0])

    const [dataHumedad, setDataHumedad] = useState([0])
    const [dataPorcentaje, setDataPorcentaje] = useState([0])

    useInterval(() => {
        fetch(`https://grupo17.pythonanywhere.com/ultimo`, {
            method: 'GET',
        })
            .then(res => res.json())
            .catch(err => {
                //console.error('Error:', err)
                //alert("Ocurrio un error, ver la consola")
            })
            .then(response => {
                const datos = response[0]

                setDataExterna([datos.temperatura_externa])
                setDataInterna([datos.temperatura_interna])
                setDataHumedad([datos.humedad_tierra])
                setDataPorcentaje([datos.porcentaje])
            })
    }, 2000);

    return (
        <div className="divP">
            <h1>Dashboard en tiempo real</h1>


            <div style={{ display: "flex", flexWrap: "wrap", height: "75vh", width: "80%", margin: "auto", marginTop: "2%" }}>
                <div className="divs">
                    <h3>Temperatura Externa</h3>
                    <BarChart name="Externa" data={dataExterna}></BarChart>
                </div>
                <div className="divs">
                    <h3>Temperatura Interna</h3>
                    <BarChart name="Interna" data={dataInterna}></BarChart>
                </div>
                <div className="divs">
                    <h3>Humedad de la Tierra</h3>
                    <PieChart data={dataHumedad}></PieChart>
                </div>
                <div className="divs">
                    <h3>Porcentaje de agua</h3>
                    <PieChart data={dataPorcentaje}></PieChart>
                </div>
            </div>

        </div>
    );
}

export default Real