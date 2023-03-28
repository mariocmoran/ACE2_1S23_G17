
import { useState } from "react";
import { setUser, getUser } from "./Global.js";

function Datos() {
    const [nombre, setNombre] = useState(getUser);

    const handleSubmit = (event) => {
        event.preventDefault(); // Evita que se recargue la página al enviar el formulario
        setNombre(event.target[0].value)
        console.log("working", event.target[0].value);

        var obj = {
            "Usuario": event.target[0].value
        }
        
        //const CORS_PROXY = 'https://cors-anywhere.herokuapp.com/';

        fetch(`https://grupo17.pythonanywhere.com/usuario`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json',
                'Access-Control-Allow-Origin': 'all'
              },
            body: JSON.stringify(obj),
        })
            .then(res => res.json())
            .catch(err => {
                console.error('Error:', err)
                //alert("Ocurrio un error, ver la consola")
            })
            .then(response => {
                console.log(response)
            })

        setUser(event.target[0].value);
    };
    return (
        <div>
            <p className="fs-5 text-end"> <span className="fw-bold text-end">Usuario:</span> {nombre}</p>
            <div style={{ width: "40%", margin: "auto", marginTop: "5%" }}>
                <center><h1>USUARIO</h1></center>
                <form style={{ marginTop: "5%" }} onSubmit={handleSubmit}>
                    <div className="mb-3">
                        <label htmlFor="exampleInputEmail1" className="form-label">Usuario</label>
                        <input type="text" className="form-control" id="exampleInputEmail1" defaultValue={nombre} />
                    </div>
                    <center><button type="submit" className="btn btn-primary">Establecer datos</button></center>
                </form>
            </div>
        </div>

    );
}

export default Datos;
