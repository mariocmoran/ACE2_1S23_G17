
import LineChart from "./graficas/LineChart";
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

function Tiempo() {

    const [dataExterna, setDataExterna] = useState([])
    const [dataInterna, setDataInterna] = useState([])
    const [dataHumedad, setDataHumedad] = useState([])
    const [dataPorcentaje, setDataPorcentaje] = useState([])
    const [dataActivacion, setDataActivacion] = useState([])

    const [labelFechas, setFechas] = useState([])

    const [dateInit, setDateInit] = useState("2023-01-01");
    const [dateFin, setDateFin] = useState("2023-12-31");

    const [horaInit, sethoraInit] = useState("00:00:00");
    const [horaFin, sethoraFin] = useState("00:00:00");

    const handleSubmit = (event) => {
        event.preventDefault(); // Evita que se recargue la página al enviar el formulario
        if (event.target[0].value !== "" && event.target[1].value !== "") {
            //console.log("working", event.target[0].value, event.target[1].value);  
            //console.log("working", event.target[2].value, event.target[3].value);  
            setDateInit(event.target[0].value);
            sethoraInit(event.target[1].value);

            setDateFin(event.target[2].value);
            sethoraFin(event.target[3].value);
        } else {
            alert("Por favor ingrese ambos parámetros.")
        }

    };


    useInterval(() => {

        var inicio = dateInit + " " + horaInit
        var fin = dateFin + " " + horaFin

        fetch(`https://grupo17.pythonanywhere.com/data?fecha1=${inicio}&fecha2=${fin}`)
            .then(response => response.json())
            .catch(error => console.error(error))
            .then(data => {

                var texterna = []
                var tinterna = []
                var htierra = []
                var pagua = []
                var activacion = []

                var ff = []

                data.map((dato) => {
                    texterna.push(dato.temperatura_externa)
                    tinterna.push(dato.temperatura_interna)
                    htierra.push(dato.humedad_tierra)
                    pagua.push(dato.porcentaje)
                    activacion.push(dato.estado)

                    const fecha = new Date(dato.fecha);

                    const dia = fecha.getDate().toString().padStart(2, "0");
                    const mes = (fecha.getMonth() + 1).toString().padStart(2, "0");
                    const anio = fecha.getFullYear();
                    const hora = fecha.getHours().toString().padStart(2, "0");
                    const minutos = fecha.getMinutes().toString().padStart(2, "0");

                    const fechaFormateada = `${dia}/${mes}/${anio} ${hora}:${minutos}`;

                    ff.push(fechaFormateada)

                    return 0;
                });

                setDataExterna(texterna)
                setDataInterna(tinterna)
                setDataHumedad(htierra)
                setDataPorcentaje(pagua)
                setDataActivacion(activacion)

                setFechas(ff)

            })

    }, 2000);

    return (
        <div className="divP">
            <h1>Dashboard a través del tiempo</h1>

            <form style={{ width: "30%", margin: "auto", marginTop: "3%" }} onSubmit={handleSubmit}>
                <div className="mb-2">
                    <label className="form-label">Inicio:</label>
                    <input type="date" className="form-control" defaultValue={dateInit} />
                    <input type="time" className="form-control" step="1" defaultValue={horaInit} />
                </div>
                <div className="mb-2">
                    <label className="form-label">Fin:</label>
                    <input type="date" className="form-control" defaultValue={dateFin} />
                    <input type="time" className="form-control" step="1" defaultValue={horaFin} />
                </div>
                <center><button type="submit" className="btn btn-primary">Establecer datos</button></center>
            </form>

            <div style={{ display: "flex", flexWrap: "wrap", height: "75vh", width: "95%", margin: "auto", marginTop: "2%", marginBottom: "3px", justifyContent: "center" }}>
                <div className="divs2">
                    <h3>Temperatura Externa</h3>
                    <LineChart data={dataExterna} label={labelFechas}></LineChart>
                </div>
                <div className="divs2">
                    <h3>Temperatura Interna</h3>
                    <LineChart data={dataInterna} label={labelFechas}></LineChart>
                </div>
                <div className="divs2">
                    <h3>Humedad de la Tierra</h3>
                    <LineChart data={dataHumedad} label={labelFechas}></LineChart>
                </div>
                <div className="divs2">
                    <h3>Porcentaje de Agua</h3>
                    <LineChart data={dataPorcentaje} label={labelFechas}></LineChart>
                </div>
                <div className="divs2">
                    <h3>Periodo de Activación</h3>
                    <LineChart data={dataActivacion} label={labelFechas}></LineChart>
                </div>
            </div>
        </div>
    );
}

export default Tiempo