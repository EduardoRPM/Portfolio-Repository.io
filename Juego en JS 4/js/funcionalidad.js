// Variables globales
    var nombre;
    var tam;
    var tablero;
    var contador = 0;
    var timer;
    var segundos = 0;

    function iniciarJuego(){
        nombre = prompt("Ingresa tu nombre");

        do {
            tam = parseInt(prompt("Ingresa el tamaño del tablero (mínimo 3):"), 10);
        } while (isNaN(tam) || tam < 3);
        
        let contenedor = document.querySelector(".tablero");
        contenedor.innerHTML = ""; // Limpiar el tablero si ya existe
        contenedor.style.width = `${(80 * tam) + 20}px`; // Ajustar el ancho dinámicamente
        contenedor.style.display = "flex";
        contenedor.style.flexWrap = "wrap";


        //Crear el arrgelo bidimensional tamXtam
        tablero = new Array(tam);
        for(var i=0; i<tam; i++){
            tablero[i] = new Array(tam);
        }

        //Crear el tablero en el HTML
        for (let i = 0; i < tam; i++) {
            for (let j = 0; j < tam; j++) {
                let celda = document.createElement("div"); // Crear un div
                celda.id = `${i}${j}`; // Asignar un ID único basado en la posición


                celda.onclick = function() {
                    moverFicha(i, j);
                };

                contenedor.appendChild(celda); // Agregar la celda al contenedor
            }
            //contenedor.appendChild(document.createElement("br")); // Salto de línea para nueva fila
        }



        //Inicializar en cero cada casilla
        for(var i=0; i<tam; i++){
            for(var j=0; j<tam; j++){
                tablero[i][j] = 0;
            }
        }

    


        //generar las fichas en posiciones aleatorias
        generarFichas();
        



        //imprimirTablero();
        document.getElementsByClassName("nombre")[0].innerHTML = nombre;
        if (timer) clearInterval(timer); // Evita múltiples temporizadores
        segundos = 0;
        document.getElementsByClassName("tiempo")[0].innerHTML = segundos;
        timer = setInterval(() => {
            segundos++;
            document.getElementsByClassName("tiempo")[0].innerHTML = segundos;
        }, 1000);

        let win = 0;

/*         for(var i=0; i<tam; i++){
            for(var j=0; j<tam; j++){
                tablero[i][j] = win+1;
                win++;
                if (i==tam-1 && j==tam-2){
                    tablero[i][j] = 0;
                    win--;
                }
            }
        } */


        //generaGanadorCaracol();
        actualizarTablero() 
    }


    function imprimirTablero(){
        for(var i=0; i<tam; i++){
            console.log(tablero[i]);
        }
    }



    function generarFichas() {
        for (var i = 0; i < (tam * tam); i++) {
            var x = Math.floor(Math.random() * tam);
            var y = Math.floor(Math.random() * tam);
            if (tablero[x][y] === 0) {
                tablero[x][y] = i;
                let cell = document.getElementById(x + "" + y);
                cell.innerHTML = tablero[x][y];
                cell.style.backgroundColor = tablero[x][y] === 0 ? "white" : "rgb(53,53,53)"; // Cambia color si es 0
            } else {
                i--;  // Vuelve a intentar si la celda ya está ocupada
            }
        }
    }


    function moverFicha(PosI, PosJ) {
        
        let Posicion = validarMovimiento(PosI, PosJ);
        if (Posicion === -1) return;
    
        // Mover la ficha en el tablero
        tablero[Posicion[0]][Posicion[1]] = tablero[PosI][PosJ];
        tablero[PosI][PosJ] = 0;
    
        // Actualizar el contenido HTML y color
        let celdaMov = document.getElementById(Posicion[0] + "" + Posicion[1]);
        let celdaVacia = document.getElementById(PosI + "" + PosJ);
    
        celdaMov.innerHTML = tablero[Posicion[0]][Posicion[1]];
        celdaVacia.innerHTML = "";
    
        celdaMov.style.backgroundColor =  "rgb(53,53,53)"; 
        celdaVacia.style.backgroundColor = "white"; // Fondo blanco para celda vacía
    
        imprimirTablero();
        verificarGanador();
        verificarGanadorCaracol();
    }


    function validarMovimiento(PosI, PosJ) {
        PosI = parseInt(PosI, 10);
        PosJ = parseInt(PosJ, 10);
        // Verificar movimiento hacia arriba
        if (PosI - 1 >= 0 && tablero[PosI - 1][PosJ] === 0) {
            return [PosI - 1, PosJ];
        }
        // Verificar movimiento hacia abajo
        if (PosI + 1 < tam && tablero[PosI + 1][PosJ] === 0) {
            return [PosI + 1, PosJ];
        }
        // Verificar movimiento hacia la izquierda
        if (PosJ - 1 >= 0 && tablero[PosI][PosJ - 1] === 0) {
            return [PosI, PosJ - 1];
        }
        // Verificar movimiento hacia la derecha
        if (PosJ + 1 < tam && tablero[PosI][PosJ + 1] === 0) {
            return [PosI, PosJ + 1];
        }
        //alert("Movimiento no válido");
        // Si no hay movimiento válido, retorna -1
        return -1;
    }


    function generaGanadorCaracol() {
        // Generar un arreglo con las posiciones en orden espiral (caracol)
        let posiciones = [];
        let top = 0, bottom = tam - 1, left = 0, right = tam - 1;
        
        while (top <= bottom && left <= right) {
            // Recorrer la fila superior de izquierda a derecha
            for (let j = left; j <= right; j++) {
                posiciones.push([top, j]);
            }
            top++;
            // Recorrer la columna derecha de arriba hacia abajo
            for (let i = top; i <= bottom; i++) {
                posiciones.push([i, right]);
            }
            right--;
            // Recorrer la fila inferior de derecha a izquierda
            if (top <= bottom) {
                for (let j = right; j >= left; j--) {
                    posiciones.push([bottom, j]);
                }
                bottom--;
            }
            // Recorrer la columna izquierda de abajo hacia arriba
            if (left <= right) {
                for (let i = bottom; i >= top; i--) {
                    posiciones.push([i, left]);
                }
                left++;
            }
        }
        
        // Número total de casillas
        let total = tam * tam;
        
        // Llenar el tablero en el orden "caracol" con números del 1 al total-1 
        // y colocar 0 en la última posición (la casilla vacía)
        for (let idx = 0; idx < posiciones.length; idx++) {
            let [i, j] = posiciones[idx];
            if (idx < total - 1) {
                tablero[i][j] = idx + 1;
            } else {
                tablero[i][j] = 0;
            }
        }
        
        // Para dejar solo un movimiento para ganar, se intercambian los dos últimos valores
        // de la secuencia. Esto hará que el tablero esté casi resuelto y solo se deba mover
        // la ficha adyacente al espacio vacío.
        if (posiciones.length >= 2) {
            let ultimoIdx = posiciones.length - 1;
            let penultimoIdx = posiciones.length - 2;
            let [i1, j1] = posiciones[ultimoIdx];
            let [i2, j2] = posiciones[penultimoIdx];
            let temp = tablero[i1][j1];
            tablero[i1][j1] = tablero[i2][j2];
            tablero[i2][j2] = temp;
        }
    }
    

    function verificarGanador() {
        contador++;
        document.getElementsByClassName("Contador")[0].innerHTML = contador; 
        let gano = 1; 

        for (let i = 0; i < tam; i++) {
            for (let j = 0; j < tam; j++) {
                if (i === tam - 1 && j === tam - 1) {
                    if (tablero[i][j] !== 0) return;
                } else {
                    if (tablero[i][j] !== gano) return; // no está en orden, salir
                    gano++; 
                }
            }
        }

        clearInterval(timer); // Detener el temporizador cuando el jugador gana
        alert(`¡Ganaste en ${segundos} segundos con ${contador} movimientos!`);
    }



    function verificarGanadorCaracol() {
        let n = tam;
        let i = 0, j = 0;
        let direccion = 0;
        let desplazamientosFila = [0, 1, 0, -1];
        let desplazamientosColumna = [1, 0, -1, 0];
        let movimiento = 1;
        let visitadas = [];
        for (let i = 0; i < n; i++) {
            visitadas.push(new Array(n).fill(false));
        }
        let correcto = true;
    
        while (movimiento < n * n) { // Verificar hasta (n*n -1)
            if (tablero[i][j] !== movimiento) {
                correcto = false;
                break;
            }
            visitadas[i][j] = true;
            let nuevaFila = i + desplazamientosFila[direccion];
            let nuevaColumna = j + desplazamientosColumna[direccion];
            let fueraDeLimite = nuevaFila < 0 || nuevaFila >= n || nuevaColumna < 0 || nuevaColumna >= n;
            let yaVisitada = !fueraDeLimite && visitadas[nuevaFila][nuevaColumna];
            if (fueraDeLimite || yaVisitada) {
                direccion = (direccion + 1) % 4;
                nuevaFila = i + desplazamientosFila[direccion];
                nuevaColumna = j + desplazamientosColumna[direccion];
            }
            i = nuevaFila;
            j = nuevaColumna;
            movimiento++;
        }
    
        // Verificar la última celda (0) y si todo fue correcto
        if (correcto && tablero[i][j] === 0) {
            clearInterval(timer);
            alert(`¡Ganaste en forma de Caracol en ${segundos} segundos con ${contador} movimientos!`);
        } else {
            // alert("No está en orden");
        }
    }
    




function actualizarTablero() {
    // Recorrer todas las filas del tablero
    for (let i = 0; i < tablero.length; i++) {
        for (let j = 0; j < tablero[i].length; j++) {
            // Construir el id del div en base a la posición del tablero
            let id = i + "" + j;
            let cell = document.getElementById(id);  // Obtener el div por id
            
            // Actualizar el contenido del div con el valor correspondiente del tablero
            if (tablero[i][j] === 0) {
                cell.innerHTML = '';  // Si el valor es 0, dejamos la celda vacía (o puedes poner un espacio, etc.)
                cell.style.backgroundColor = 'white';  // Opcional: cambiar el color de fondo
            } else {
                cell.innerHTML = tablero[i][j];  // Si tiene un número, lo mostramos
                cell.style.backgroundColor = "rgb(53,53,53)";  // Cambiar el color de fondo de las celdas con números
            }
        }
    }
}


