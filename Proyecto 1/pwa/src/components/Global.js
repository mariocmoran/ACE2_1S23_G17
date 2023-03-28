//localStorage.setItem('usuario', 'None');

export function setUser(nuevoValor) {
    localStorage.setItem('usuario', nuevoValor);
}

export function getUser() {
  return localStorage.getItem('usuario');
}