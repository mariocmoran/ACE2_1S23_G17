import { getUser } from "./Global.js";

function Valores() {
    const handleSubmit = (event) => {
        event.preventDefault(); // Evita que se recargue la página al enviar el formulario
        console.log("working", event.target[0].value, event.target[1].value)

        var obj = {
            "Tiempo_Trabajo": event.target[0].value,
            "Tiempo_Descanso": event.target[1].value
        }

        fetch(`https://grupo17.pythonanywhere.com/tiempotd`, {
            method: 'PUT',
            headers: {
                'Content-Type': 'application/json'
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
    };
    return (
        <div>
            <p className="fs-5 text-end"> <span className="fw-bold text-end">Usuario:</span> {getUser()}</p>
            <div style={{ width: "40%", margin: "auto", marginTop: "5%" }}>
                <center><h1>VALORES PARA EL POMODORO</h1></center>
                <form style={{ marginTop: "5%" }} onSubmit={handleSubmit}>
                    <div className="mb-3">
                        <label htmlFor="trabajo" className="form-label">Minutos de trabajo</label>
                        <input type="number" id="trabajo" className="form-control" min="1" defaultValue="25"></input>
                    </div>
                    <div className="mb-3">
                        <label htmlFor="descanso" className="form-label">Minutos de descanso</label>
                        <input type="number" id="descanso" className="form-control" min="1" defaultValue="5"></input>
                    </div>
                    <center><button type="submit" className="btn btn-primary">Establecer datos</button></center>
                </form>
            </div>
        </div>

    );
}

export default Valores;

