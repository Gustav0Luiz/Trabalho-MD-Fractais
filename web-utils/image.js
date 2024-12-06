// Seleção de elementos do DOM
const fileInput = document.getElementById("file-input");
const angleInput = document.getElementById("angle-input");
const generateButton = document.getElementById("generate-button");
const canvas = document.getElementById("canvasFractal");
const ctx = canvas.getContext("2d");
const resetButton = document.getElementById("reset-button");
const zoomInButton = document.getElementById("zoom-in-button");
const zoomOutButton = document.getElementById("zoom-out-button");

// Variáveis de estado
let fractalString = ""; // String do fractal lida do arquivo
let angle = 0; // Ângulo em graus
let escalaFractal = 1; // Escala para o zoom
let offsetX = 0; // Deslocamento horizontal do canvas
let offsetY = 0; // Deslocamento vertical do canvas
let isDragging = false; // Flag para arrastar
let dragStartX = 0;
let dragStartY = 0;

// Validação dos campos de entrada
generateButton.disabled = true;
function validateInputs() {
    const isFileSelected = fileInput.files.length > 0;
    const isAngleProvided = angleInput.value.trim() !== "";
    generateButton.disabled = !(isFileSelected && isAngleProvided);
}

// Eventos para validar os campos
fileInput.addEventListener("change", validateInputs);
angleInput.addEventListener("input", validateInputs);

// Função para desenhar o fractal
function drawFractal() {
    const comprimentoSegmento = 10; // Comprimento de cada segmento
    const angleRad = (angle * Math.PI) / 180; // Converte o ângulo para radianos

    // Limpa e configura o canvas
    ctx.resetTransform();
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Aplica transformações (zoom e arrasto)
    ctx.translate(canvas.width / 2, canvas.height / 2);
    ctx.scale(escalaFractal, escalaFractal);
    ctx.translate(offsetX, offsetY);

    // Posição inicial e direção
    let x = 0;
    let y = 0;
    let direction = 0;

    ctx.beginPath();
    ctx.moveTo(x, y);

    // Processa cada símbolo da string
    for (const char of fractalString) {
        switch (char) {
            case "F":
                const newX = x + Math.cos(direction) * comprimentoSegmento;
                const newY = y + Math.sin(direction) * comprimentoSegmento;
                ctx.lineTo(newX, newY);
                x = newX;
                y = newY;
                break;
            case "+":
                direction += angleRad;
                break;
            case "-":
                direction -= angleRad;
                break;
        }
    }

    // Finaliza o desenho
    ctx.strokeStyle = "#000";
    ctx.lineWidth = 1;
    ctx.stroke();
}

// Função para carregar o fractal e desenhá-lo
generateButton.addEventListener("click", () => {
    if (!fileInput.files[0]) return;

    const reader = new FileReader();
    reader.onload = function (event) {
        fractalString = event.target.result.trim();
        angle = parseFloat(angleInput.value);
        if (isNaN(angle)) {
            alert("Ângulo inválido. Digite um número válido.");
            return;
        }
        drawFractal();
    };

    reader.onerror = () => alert("Erro ao ler o arquivo.");
    reader.readAsText(fileInput.files[0]);
});

// Eventos de zoom com scroll
canvas.addEventListener("wheel", (event) => {
    event.preventDefault();

    const zoomStep = 0.1;
    const mouseX = canvas.width / 2 / escalaFractal - offsetX;
    const mouseY = canvas.height / 2 / escalaFractal - offsetY;

    const previousScale = escalaFractal;
    escalaFractal += event.deltaY < 0 ? zoomStep : -zoomStep;
    escalaFractal = Math.max(0.1, Math.min(escalaFractal, 5)); // Limita o zoom

    offsetX -= mouseX * (escalaFractal - previousScale);
    offsetY -= mouseY * (escalaFractal - previousScale);

    drawFractal();
});

// Eventos para arrastar o canvas
canvas.addEventListener("mousedown", (event) => {
    isDragging = true;
    dragStartX = event.offsetX / escalaFractal - offsetX;
    dragStartY = event.offsetY / escalaFractal - offsetY;
});

canvas.addEventListener("mousemove", (event) => {
    if (isDragging) {
        offsetX = event.offsetX / escalaFractal - dragStartX;
        offsetY = event.offsetY / escalaFractal - dragStartY;
        drawFractal();
    }
});

canvas.addEventListener("mouseup", () => (isDragging = false));
canvas.addEventListener("mouseleave", () => (isDragging = false));

// Função para aplicar zoom (usada nos botões de zoom)
function applyZoom(factor) {
    const zoomStep = 0.1;

    // Ponto de referência do zoom (centro do canvas)
    const mouseX = canvas.width / 2 / escalaFractal - offsetX;
    const mouseY = canvas.height / 2 / escalaFractal - offsetY;

    const previousScale = escalaFractal;
    escalaFractal += factor * zoomStep;

    // Limita o zoom mínimo e máximo
    escalaFractal = Math.max(0.1, Math.min(escalaFractal, 5));

    // Ajusta o deslocamento para centralizar o zoom
    offsetX -= mouseX * (escalaFractal - previousScale);
    offsetY -= mouseY * (escalaFractal - previousScale);

    drawFractal();
}

// Eventos para zoom in e zoom out
zoomInButton.addEventListener("click", () => {
    applyZoom(1); // Zoom in
});

zoomOutButton.addEventListener("click", () => {
    applyZoom(-1); // Zoom out
});

// Evento para recentralizar o canvas
resetButton.addEventListener("click", () => {
    offsetX = 0; // Redefine deslocamento horizontal
    offsetY = 0; // Redefine deslocamento vertical
    escalaFractal = 1; // Redefine o zoom
    drawFractal(); // Redesenha o fractal
});
