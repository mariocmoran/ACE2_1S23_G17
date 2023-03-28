import React, { useState, useEffect, useRef } from "react";
import { getUser } from "./Global.js";
import BarChart from "./graficas/BarChart.js";

import parado from './parado.png'
import sentado from './sentado.png'


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

function Real() {

    const [data1, setData1] = useState([]);
    const [data2, setData2] = useState([]);

    const [img, setImg] = useState();

    const [imgStyle1, setimgStyle1] = useState();

    const [data3, setData3] = useState([]);

    useInterval(() => {
        fetch(`https://grupo17.pythonanywhere.com/ultimo`, {
            method: 'GET',
        })
            .then(res => res.json())
            .catch(err => {
                console.error('Error:', err)
                //alert("Ocurrio un error, ver la consola")
            })
            .then(response => {
                var ndata = [{ total: response[0].Penalizacion_No_S, init: "", end: "", name: "Penalización Trabajo" }]
                setData1(ndata);
                ndata = [{ total: response[0].Penalizacion_No_P, init: "", end: "", name: "Penalización Descanso" }]
                setData2(ndata);
                if (response[0].Estado === 1) {
                    setImg(parado)
                    setimgStyle1({ width: "80%" })
                } else {
                    setImg(sentado)
                    setimgStyle1({ width: "50%" })
                }

                ndata = []
                var ps = ((response[0].Penalizacion_No_S / 60) / (response[0].Tiempo_Trabajo)) * 100
                var pp = ((response[0].Penalizacion_No_P / 60) / (response[0].Tiempo_Descanso)) * 100
                var completo = { total: 100 - ps, init: "", end: "", name: "Trabajo" }
                var penS = { total: ps, init: "", end: "", name: "PT" }

                var dd = { total: 100 - pp, init: "", end: "", name: "Descanso" }
                var penP = { total: pp, init: "", end: "", name: "PD" }
                ndata.push(completo)
                ndata.push(penS)
                ndata.push(dd)
                ndata.push(penP)
                setData3(ndata);
            })
    }, 1000);

    return (
        <div>
            <p className="fs-5 text-end"> <span className="fw-bold text-end">Usuario:</span> {getUser()}</p>
            <div style={{ width: "95%", margin: "auto", marginTop: "5%", marginBottom: "5%" }}>
                <center><h1>INFORME EN TIEMPO REAL</h1></center>
                <div className="container" style={{ marginTop: "5%" }}>
                    <div className="row">
                        <div className="col-md-6 col-sm-6 box">
                            <h4>Penalización por no sentarse a tiempo </h4>
                            <BarChart data={data1} name="Penalización (s)" color="#FF5E5E" color2="black" />
                        </div>
                        <div className="col-md-6 col-sm-6 box">
                            <h4> Penalización por no pararse a tiempo</h4>
                            <BarChart data={data2} name="Penalización (s)" color="#FF5E5E" color2="black" />
                        </div>
                    </div>
                    <div className="row">
                        <div className="col-md-6 col-sm-6 box">
                            <h4>Validación de que el usuario esté sentado </h4>
                            <center><img src={img} alt="Imagen" style={{ maxWidth: "100%", maxHeight: "100%", ...imgStyle1 }} /></center>
                        </div>
                        <div className="col-md-6 col-sm-6 box">
                            <h4>Porcentajes de cumplimiento</h4>
                            <BarChart data={data3} name="Cumplimiento (%)" color="#B7FC8A" color2="#FF5E5E" color3="#B7FC8A" color4="#FF5E5E" />
                        </div>
                    </div>
                </div>
            </div>
        </div>

    );
}

export default Real;