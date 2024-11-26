const canvas = document.getElementById('canvasFractal');
const ctx = canvas.getContext('2d');

// Variáveis para gerenciar as etapas
let etapa = 0;
let stringAtual = ''; // Base inicial para as iterações
let historico = []; // Histórico das strings geradas
let escalaFractal = 1; // Escala aplicada para o zoom
const axiomaInput = document.getElementById('axioma'); // Axioma dinâmico
const regrasInput = document.getElementById('regras');
const anguloInput = document.getElementById('angulo');

// Variáveis para o deslocamento do canvas
let offsetX = 0;
let offsetY = 0;
let isDragging = false; // Indica se o usuário está arrastando
let dragStartX = 0;
let dragStartY = 0;

// Função para aplicar as regras de substituição
function aplicarRegras(string, regras) {
    const regraMap = {};
    regras.split(',').forEach(regra => {
        const [chave, valor] = regra.split('→');
        regraMap[chave.trim()] = valor.trim();
    });

    return string.split('').map(simbolo => regraMap[simbolo] || simbolo).join('');
}

// Função para calcular os limites do fractal
function calcularLimites(string, comprimentoSegmento) {
    let minX = 0, maxX = 0, minY = 0, maxY = 0;
    let posX = 0, posY = 0;
    let direcao = 0;
    const angulo = parseFloat(anguloInput.value) * (Math.PI / 180);

    for (const simbolo of string) {
        if (simbolo === 'F') {
            posX += Math.cos(direcao) * comprimentoSegmento;
            posY += Math.sin(direcao) * comprimentoSegmento;
            minX = Math.min(minX, posX);
            maxX = Math.max(maxX, posX);
            minY = Math.min(minY, posY);
            maxY = Math.max(maxY, posY);
        } else if (simbolo === '+') {
            direcao += angulo;
        } else if (simbolo === '-') {
            direcao -= angulo;
        }
    }

    return { minX, maxX, minY, maxY };
}

// Função para desenhar o fractal no canvas
function desenharFractal(string) {
    const comprimentoSegmento = 10; // Comprimento padrão do segmento

    // Limpa o canvas e ajusta transformações
    ctx.resetTransform();
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Aplica o zoom e centralização
    ctx.translate(canvas.width / 2, canvas.height / 2); // Centraliza o ponto inicial
    ctx.scale(escalaFractal, escalaFractal); // Aplica o zoom
    ctx.translate(offsetX, offsetY); // Aplica deslocamento

    // Inicializa posição e direção
    let posX = 0;
    let posY = 0;
    let direcao = 0;

    // Configuração inicial do desenho
    ctx.beginPath();
    ctx.moveTo(posX, posY);

    // Processa cada símbolo da string
    for (const simbolo of string) {
        if (simbolo === 'F') {
            const novoX = posX + Math.cos(direcao) * comprimentoSegmento;
            const novoY = posY + Math.sin(direcao) * comprimentoSegmento;
            ctx.lineTo(novoX, novoY);
            posX = novoX;
            posY = novoY;
        } else if (simbolo === '+') {
            direcao += parseFloat(anguloInput.value) * (Math.PI / 180); // Vira à direita
        } else if (simbolo === '-') {
            direcao -= parseFloat(anguloInput.value) * (Math.PI / 180); // Vira à esquerda
        }
    }

    ctx.stroke();
}

// Inicializa o fractal com o axioma inserido
function inicializarAxioma() {
    const axioma = axiomaInput.value.trim(); // Captura o axioma do input
    stringAtual = axioma; // Define o axioma como a configuração inicial
    historico = [axioma]; // Inicializa o histórico com o axioma
    etapa = 0; // Redefine a etapa
    escalaFractal = 1; // Reseta a escala
    offsetX = 0;
    offsetY = 0; // Reseta deslocamento
    document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
    desenharFractal(stringAtual);
}

// Evento para inicializar com o axioma
axiomaInput.addEventListener('change', inicializarAxioma);

// Evento para avançar iteração
document.getElementById('btnAvancar').addEventListener('click', () => {
    const regras = regrasInput.value.trim();
    stringAtual = aplicarRegras(stringAtual, regras);
    historico.push(stringAtual); // Salva no histórico

    etapa++;
    document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
    desenharFractal(stringAtual);
});

// Evento para retroceder iteração
document.getElementById('btnRetroceder').addEventListener('click', () => {
    if (etapa > 0) {
        historico.pop(); // Remove a última string gerada
        stringAtual = historico[historico.length - 1]; // Volta para a string anterior
        etapa--;
        document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
        desenharFractal(stringAtual);
    } 
});

// Evento para controlar o zoom com o scroll
canvas.addEventListener('wheel', (event) => {
    event.preventDefault();

    // Posição do mouse relativa ao canvas
    const mouseX = (event.offsetX - canvas.width / 2) / escalaFractal - offsetX;
    const mouseY = (event.offsetY - canvas.height / 2) / escalaFractal - offsetY;

    // Ajusta o zoom
    const zoomStep = 0.1;
    const prevScale = escalaFractal;
    if (event.deltaY < 0) {
        escalaFractal *= 1 + zoomStep; // Zoom in
    } else {
        escalaFractal *= 1 - zoomStep; // Zoom out
    }

    // Limita o zoom mínimo e máximo
    escalaFractal = Math.max(0.1, Math.min(escalaFractal, 5));

    // Ajusta o deslocamento para manter o zoom focado no ponto do mouse
    offsetX -= mouseX * (escalaFractal - prevScale);
    offsetY -= mouseY * (escalaFractal - prevScale);

    desenharFractal(stringAtual);
});

// Evento para clicar e arrastar
canvas.addEventListener('mousedown', (event) => {
    isDragging = true;
    dragStartX = event.offsetX / escalaFractal - offsetX;
    dragStartY = event.offsetY / escalaFractal - offsetY;
});

canvas.addEventListener('mousemove', (event) => {
    if (isDragging) {
        offsetX = event.offsetX / escalaFractal - dragStartX;
        offsetY = event.offsetY / escalaFractal - dragStartY;
        desenharFractal(stringAtual);
    }
});

canvas.addEventListener('mouseup', () => {
    isDragging = false;
});

canvas.addEventListener('mouseleave', () => {
    isDragging = false;
});

// Inicializa o fractal com o valor inicial do input
inicializarAxioma();
