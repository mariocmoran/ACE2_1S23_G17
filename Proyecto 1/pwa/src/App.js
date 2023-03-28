import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';
import Datos from './components/Datos';
import Valores from './components/Valores';
import Graficas from './components/Graficas';
import Real from './components/Real';
import './App.css';

function App() {
  return (
    <div className='App'><BrowserRouter>
      <nav className="navbar navbar-expand-lg bg-body-tertiary" data-bs-theme="dark">
        <div className="container-fluid">
          <span className="navbar-brand" >Pomodoro</span>
          <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
            <span className="navbar-toggler-icon"></span>
          </button>
          <div className="collapse navbar-collapse" id="navbarNav">
            <ul className="navbar-nav">
              <li className="nav-item">
                <Link to="/" className="nav-link">Usuario</Link>
              </li>
              <li className="nav-item">
                <Link to="/Valores" className="nav-link" >Valores</Link>
              </li>
              <li className="nav-item dropdown">
                <a className="nav-link dropdown-toggle" href="#" role="button" data-bs-toggle="dropdown" aria-expanded="false">
                  Informe
                </a>
                <ul className="dropdown-menu">
                  <li><Link to="/Graficas" className="nav-link">A través del tiempo</Link></li>
                  <li><Link to="/Real" className="nav-link">Tiempo real</Link></li>
                </ul>
              </li>
            </ul>
          </div>
        </div>
      </nav>
      <Routes>
        <Route path="/" element={<Datos />} />
        <Route path="/Graficas" element={<Graficas />} />
        <Route path="/Valores" element={<Valores />} />
        <Route path="/Real" element={<Real />} />
      </Routes>
    </BrowserRouter></div>

  );
}

export default App;
