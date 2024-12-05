const canvas = document.getElementById('fractalCanvas');
const ctx = canvas.getContext('2d');

// Função para desenhar o fractal
function drawFractal(fractalString) {
    // Limpa o canvas
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.resetTransform();  // Reseta transformações anteriores
    ctx.translate(canvas.width / 2, canvas.height / 2);  // Centraliza o ponto de origem
    ctx.beginPath();
    ctx.moveTo(0, 0);  // Começa do centro do canvas

    let angle = Math.PI / 2;  // Ângulo inicial (90 graus)
    let length = 10;          // Comprimento inicial do segmento

    // Percorre a string do fractal
    for (let i = 0; i < fractalString.length; i++) {
        const command = fractalString[i];

        if (command === 'F') {
            // Desenha o segmento "F"
            ctx.lineTo(Math.cos(angle) * length, Math.sin(angle) * length);
            ctx.stroke();
            ctx.moveTo(Math.cos(angle) * length, Math.sin(angle) * length);
        } else if (command === '+') {
            // Gira para a direita
            angle += Math.PI / 3;  // Aumenta o ângulo de 60 graus
        } else if (command === '-') {
            // Gira para a esquerda
            angle -= Math.PI / 3;  // Diminui o ângulo de 60 graus
        }
    }
}

// Função para gerar o fractal a partir da string inserida
document.getElementById('generateFractal').addEventListener('click', () => {
    const fractalString = document.getElementById('fractalString').value.trim();
    if (fractalString.length > 0) {
        // Ajusta o tamanho do canvas de acordo com o fractal
        canvas.width = 800;
        canvas.height = 600;
        drawFractal(fractalString);
    } else {
        alert('Por favor, insira uma string de fractal válida.');
    }
});
