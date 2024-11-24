Le projet vise à développer un système de régulation de température pour un four électrique.
L'objectif est de permettre à un opérateur de contrôler et de réguler la température du four via une application en C++ avec une interface utilisateur.

Le système permet à l'utilisateur de :
- Contrôler la montée en température du four en ajustant la puissance de chauffe entre 0 et 100%;
- Suivre l'évolution de la température à l'aide d'une sonde PT100 et d'un convertisseur PT100 -> tension (0 à 10V correspondant à 0 à 150°C);
- Réguler la température pour atteindre une consigne sélectionnée, comprise entre la température ambiante et 65°C, avec un échantillonnage toutes les 3 secondes;
- Afficher les données : température actuelle, courbe d'évolution de la température (T° = f(t)), et gérer la mise en marche/arrêt via une IHM.
