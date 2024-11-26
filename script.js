const canvas = document.getElementById('canvasFractal');
const ctx = canvas.getContext('2d');

// Variáveis para gerenciar as etapas
let etapa = 0;
let stringAtual = ''; // Base inicial para as iterações
let historico = []; // Histórico das strings geradas
let zoomHistorico = [1]; // Histórico do zoom para cada etapa
const axiomaInput = document.getElementById('axioma'); // Axioma dinâmico
const regrasInput = document.getElementById('regras');
const anguloInput = document.getElementById('angulo');

// Função para aplicar as regras de substituição
function aplicarRegras(string, regras) {
    const regraMap = {};
    regras.split(',').forEach(regra => {
        const [chave, valor] = regra.split('→');
        regraMap[chave.trim()] = valor.trim();
    });

    // Processa cada símbolo da string e aplica as regras, se existirem
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
function desenharFractal(string, zoom) {
    // Limpa o canvas e reseta transformações
    ctx.resetTransform();
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    // Aplica o zoom e calcula os limites
    ctx.scale(zoom, zoom);
    const comprimentoSegmento = 10; // Comprimento fixo dos segmentos
    const { minX, maxX, minY, maxY } = calcularLimites(string, comprimentoSegmento);

    // Centraliza o fractal no canvas
    const offsetX = (canvas.width / (2 * zoom)) - ((maxX + minX) / 2);
    const offsetY = (canvas.height / (2 * zoom)) - ((maxY + minY) / 2);

    // Inicializa posição e direção
    let posX = offsetX;
    let posY = offsetY;
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
    zoomHistorico = [1]; // Redefine o histórico de zoom
    document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
    desenharFractal(stringAtual, 1);
}

// Evento para inicializar com o axioma
axiomaInput.addEventListener('change', inicializarAxioma);

// Evento para avançar iteração
document.getElementById('btnAvancar').addEventListener('click', () => {
    const regras = regrasInput.value.trim();
    stringAtual = aplicarRegras(stringAtual, regras);
    historico.push(stringAtual); // Salva no histórico

    // Atualiza o zoom
    if ((etapa + 1) % 5 === 0) {
        zoomHistorico.push(zoomHistorico[zoomHistorico.length - 1] * 0.8); // Reduz zoom
    } else {
        zoomHistorico.push(zoomHistorico[zoomHistorico.length - 1]); // Mantém zoom
    }

    etapa++;
    document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
    desenharFractal(stringAtual, zoomHistorico[etapa]);
});

// Evento para retroceder iteração
document.getElementById('btnRetroceder').addEventListener('click', () => {
    if (etapa > 0) {
        historico.pop(); // Remove a última string gerada
        zoomHistorico.pop(); // Remove o zoom correspondente
        stringAtual = historico[historico.length - 1]; // Volta para a string anterior
        etapa--;
        document.getElementById('iterator_step').textContent = `Etapa: ${etapa}`;
        desenharFractal(stringAtual, zoomHistorico[etapa]);
    } 
});

// Inicializa o fractal com o valor inicial do input
inicializarAxioma();
