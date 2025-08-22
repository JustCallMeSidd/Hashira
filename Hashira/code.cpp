const fs = require('fs');

// Take filename from command line argument or default to input.json
const filename = process.argv[2] || 'input.json';
const data = JSON.parse(fs.readFileSync(filename).toString());

const n = data.keys.n;
const k = data.keys.k;

const points = [];

// Extract points
Object.keys(data).forEach(key => {
    if (!isNaN(key)) {
        const base = parseInt(data[key].base);
        const valueStr = data[key].value;
        const y = parseInt(valueStr, base);

        points.push({
            x: parseInt(key),
            y: y
        });
    }
});

const usePoints = points.slice(0, k);

// Lagrange interpolation for constant term
function lagrangeConstant(points) {
    let c = 0;
    for (let i = 0; i < points.length; i++) {
        let numerator = 1, denominator = 1;
        for (let j = 0; j < points.length; j++) {
            if (i !== j) {
                numerator *= -points[j].x;
                denominator *= (points[i].x - points[j].x);
            }
        }
        c += points[i].y * numerator / denominator;
    }
    return Math.round(c);
}

const secretC = lagrangeConstant(usePoints);

console.log('Decoded points:', usePoints);
console.log('The secret (C) / constant term is:', secretC);
