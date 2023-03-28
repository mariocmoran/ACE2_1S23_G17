import React, { useState, useEffect, useRef } from "react";
import { getUser } from "./Global.js";
import BarChart from "./graficas/BarChart.js";


function useInterval(callback, delay) {
    const savedCallback = useRef();

    // Remember the latest function.
    useEffect(() => {
        savedCallback.current = callback;
    }, [callback]);

    // Set up the interval.
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

function Graficas() {

    const [data1, setData1] = useState([]);
    const [data2, setData2] = useState([]);

    const [data3, setData3] = useState([]);
    const [data4, setData4] = useState([]);

    const [dataP, setDataP] = useState([]);
    const [dataS, setDataS] = useState([]);

    const [dateInit, setDateInit] = useState("2023-01-01");
    const [dateFin, setDateFin] = useState("2023-12-31");

    const [horaInit, sethoraInit] = useState("00:00:00");
    const [horaFin, sethoraFin] = useState("00:00:00");

    const handleSubmit = (event) => {
        event.preventDefault(); // Evita que se recargue la página al enviar el formulario
        if (event.target[0].value !== "" && event.target[1].value !== "") {
            console.log("working", event.target[0].value, event.target[1].value);  
            console.log("working", event.target[2].value, event.target[3].value);  
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
                //console.log(data)
                var ndata = []
                var ndataPS = []
                var ndataPP = []
                var ndataS = []
                var ndataP = []
                var dataCumplimientos = []

                for (var j = 0; j < data.length; j++) {

                    var fecha = new Date(data[j].Fecha);
                    const dia = fecha.getDate();
                    const mes = fecha.getMonth() + 1;
                    const anio = fecha.getFullYear();
                    const hora = fecha.getHours();
                    const minuto = fecha.getMinutes();
                    const segundo = fecha.getSeconds();

                    const fechaFormateada = `${dia.toString().padStart(2, "0")}/${mes.toString().padStart(2, "0")}/${anio} ${hora.toString().padStart(2, "0")}:${minuto.toString().padStart(2, "0")}:${segundo.toString().padStart(2, "0")}`;


                    ndataPS.push({ total: data[j].Penalizacion_No_S, init: fechaFormateada, end: "", name: "" })
                    ndataPP.push({ total: data[j].Penalizacion_No_P, init: fechaFormateada, end: "", name: "" })

                    ndataS.push({ total: data[j].Estado === 0 ? 100 : 5, init: fechaFormateada, end: "", name: "" })
                    ndataP.push({ total: data[j].Estado === 1 ? 100 : 5, init: fechaFormateada, end: "", name: "" })

                }
                setData1(ndataPS);
                setData2(ndataPP);
                

                setDataS(ndataS);
                setDataP(ndataP);



                var ultimoid
                var ultimouser
                var completo
                var penS
                var penP
                var ps
                var pp
                var dd
                var descanso
                for (var i = 0; i < data.length; i++) {
                    if (i === 0) {
                        ultimoid = data[i].No_Pomodoro
                        ultimouser = data[i].Usuario
                        completo = { total: data[i].Tiempo_Trabajo, init: data[i].Usuario, end: "", name: "Trabajo" }
                        descanso = { total: data[i].Tiempo_Descanso, init: "", end: "", name: "Descanso" }
                        penS = { total: (data[i].Penalizacion_No_S / 60), init: "", end: "", name: "PT" }
                        penP = { total: (data[i].Penalizacion_No_P / 60), init: "", end: "", name: "PD" }
                        ndata.push(completo)
                        ndata.push(descanso)
                        ndata.push(penS)
                        ndata.push(penP)

                        ps = ((data[i].Penalizacion_No_S / 60) / (data[i].Tiempo_Trabajo)) * 100
                        pp = ((data[i].Penalizacion_No_P / 60) / (data[i].Tiempo_Descanso)) * 100
                        completo = { total: 100 - ps, init: "", end: "", name: "Trabajo" }
                        penS = { total: ps, init: "", end: "", name: "PT" }

                        dd = { total: 100 - pp, init: "", end: "", name: "Descanso" }
                        penP = { total: pp, init: "", end: "", name: "PD" }
                        dataCumplimientos.push(completo)
                        dataCumplimientos.push(penS)
                        dataCumplimientos.push(dd)
                        dataCumplimientos.push(penP)
                    }

                    if (ultimoid !== data[i].No_Pomodoro || ultimouser !== data[i].Usuario) {
                        ultimoid = data[i].No_Pomodoro
                        ultimouser = data[i].Usuario

                        completo = { total: data[i].Tiempo_Trabajo, init: data[i].Usuario, end: "", name: "Trabajo" }
                        descanso = { total: data[i].Tiempo_Descanso, init: "", end: "", name: "Descanso" }
                        penS = { total: (data[i].Penalizacion_No_S / 60), init: "", end: "", name: "PT" }
                        penP = { total: (data[i].Penalizacion_No_P / 60), init: "", end: "", name: "PD" }
                        ndata.push(completo)
                        ndata.push(descanso)
                        ndata.push(penS)
                        ndata.push(penP)

                        ps = ((data[i].Penalizacion_No_S / 60) / (data[i].Tiempo_Trabajo)) * 100
                        pp = ((data[i].Penalizacion_No_P / 60) / (data[i].Tiempo_Descanso)) * 100
                        completo = { total: 100 - ps, init: "", end: "", name: "Trabajo" }
                        penS = { total: ps, init: "", end: "", name: "PT" }

                        dd = { total: 100 - pp, init: "", end: "", name: "Descanso" }
                        penP = { total: pp, init: "", end: "", name: "PD" }
                        dataCumplimientos.push(completo)
                        dataCumplimientos.push(penS)
                        dataCumplimientos.push(dd)
                        dataCumplimientos.push(penP)
                    }
                }

                setData3(dataCumplimientos);
                setData4(ndata);
            })


    }, 1000);

    return (
        <div>
            <p className="fs-5 text-end"> <span className="fw-bold text-end">Usuario:</span> {getUser()}</p>
            <div style={{ width: "95%", margin: "auto", marginTop: "5%", marginBottom: "5%" }}>
                <center><h1>INFORME A TRAVÉS DEL TIEMPO</h1></center>
                <form style={{ width: "30%", margin: "auto", marginTop: "3%" }} onSubmit={handleSubmit}>
                    <div className="mb-3">
                        <label className="form-label">Inicio:</label>
                        <input type="date" className="form-control" defaultValue={dateInit} />
                        <input type="time" className="form-control" step="1" defaultValue={horaInit} />
                    </div>
                    <div className="mb-3">
                        <label className="form-label">Fin:</label>
                        <input type="date" className="form-control" defaultValue={dateFin} />
                        <input type="time" className="form-control" step="1" defaultValue={horaFin} />
                    </div>
                    <center><button type="submit" className="btn btn-primary">Establecer datos</button></center>
                </form>
                <div className="container" style={{ marginTop: "5%" }}>
                    <div className="row">
                        <div className="col-md-4 col-sm-6 box">
                            <h4>Penalización por no sentarse a tiempo </h4>
                            <BarChart data={data1} name="Penalización (s)" color="#FF5E5E" color2="#FF5E5E" color3="#FF5E5E" color4="#FF5E5E" />
                        </div>
                        <div className="col-md-4 col-sm-6 box">
                            <h4> Penalización por no pararse a tiempo</h4>
                            <BarChart data={data2} name="Penalización (s)" color="#FF5E5E" color2="#FF5E5E" color3="#FF5E5E" color4="#FF5E5E" />
                        </div>
                        <div className="col-md-4 col-sm-6 box">
                            <h4>Validación de que el usuario esté sentado </h4>
                            <BarChart data={dataS} name="Sentado" color="#FFD157" color2="#FFD157" color3="#FFD157" color4="#FFD157" />
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-4 col-sm-6 box">
                            <h4>Validación de que el usuario este parado</h4>
                            <BarChart data={dataP} name="Parado" color="#D7FDFA" color2="#D7FDFA" color3="#D7FDFA" color4="#D7FDFA" />
                        </div>
                        <div className="col-md-4 col-sm-6 box">
                            <h4>Porcentajes de cumplimiento</h4>
                            <BarChart data={data3} name="Cumplimiento (%)" color="#B7FC8A" color2="#FF5E5E" color3="#B7FC8A" color4="#FF5E5E" />
                        </div>
                        <div className="col-md-4 col-sm-6 box">
                            <h4>Gráfica del total de pomodoros</h4>
                            <BarChart data={data4} name="Pomodoros (min)" color="#B7FC8A" color2="gray" color3="#FF0000" color4="#760000" />
                        </div>
                    </div>
                </div>
            </div>
        </div>

    );
}

export default Graficas;