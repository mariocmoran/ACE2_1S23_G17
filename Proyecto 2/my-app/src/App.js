import { BrowserRouter, Routes, Route, Link } from 'react-router-dom';
import './App.css';
import React from 'react';

import Real from './components/Real';
import Tiempo from './components/Tiempo';

function App() {
  return (
    <div className='App'><BrowserRouter>
      <nav className="navbar navbar-expand-lg" data-bs-theme="dark" style={{backgroundColor:"#212F3C"}}>
        <div className="container-fluid">
          <span className="navbar-brand" >Sistema de riego</span>
          <button className="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNav" aria-controls="navbarNav" aria-expanded="false" aria-label="Toggle navigation">
            <span className="navbar-toggler-icon"></span>
          </button>
          <div className="collapse navbar-collapse" id="navbarNav">
            <ul className="navbar-nav">
              <li className="nav-item">
                <Link to="/" className="nav-link">Tiempo Real</Link>
              </li>
              <li className="nav-item">
                <Link to="/enTiempo" className="nav-link" >A través del tiempo</Link>
              </li>
            </ul>
          </div>
        </div>
      </nav>
      <Routes>
        <Route path="/" element={<Real />} />
        <Route path="/enTiempo" element={<Tiempo />} />
      </Routes>
    </BrowserRouter></div>

  );
}

export default App;
