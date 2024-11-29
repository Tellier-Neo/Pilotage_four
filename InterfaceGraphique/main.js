
function updateValue(id, value) {
    const element = document.getElementById(id);
    element.innerText = value + (id.includes('value') ? (id === 'consigne-value' ? '°C' : '%') : '');
    
    // Met à jour les statistiques
    if (id === 'consigne-value') document.getElementById('consigne-stat').innerText = value + '°C';
    if (id === 'puissance-value') document.getElementById('puissance-stat').innerText = value + '%';
}

function chauffer() {
    const consigne = document.getElementById('consigne').value;
    const puissance = document.getElementById('puissance').value;
    const message = `Démarrage chauffage : Consigne = ${consigne}°C, Puissance = ${puissance}%`;
    document.getElementById('console-output').value += message + '\n';
    document.getElementById('temperature-actuelle').innerText = (Math.random() * consigne).toFixed(1) + '°C';
}
