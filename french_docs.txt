README

Nous avons pu coder toutes les fonctions et nous les avons testées
et notre emulateur mips fonction bien avec nos fichiers tests

cependant il est necessaire de connaitre les points important
de notre syntaxe :

En premier lieu nous avons gérer la memmonic des noms des registres ainsi 
on peut ecrire $zero au lieu de $0. (voir fonction checkRegisters dans le module 
Utility)

En outre il faut noter que pour les instructions exigeant un offset ou un target 
comme JAL target, SW $2,offset($8); il est necessaire que offset et target soient
des multiples de 4

Un autre point important est est que notre coder est robuste au espace dans l'instruction 
mips, on peut donc avoir {ADD    $4,$2   ,$5} comme {ADD $4,$2,$5} 
(voir fonction checkRegisters dans le module Utility)

En second lieu nous n avons pas mis les etats des registres dans un fichier texte 
nous les affichons dans la console 

Aussi on a pris en compte les caracteres blanc que nous arrivons a identifie et ignoré
sauf un seul qui nous pose probleme . Nous ne le connaissons pas mais il fait des suppressions sur la 
ligne ou il est placé .
Nous avons fait des recherches et demandé l'aide d'un prof de TD mais nous n'avons pas pu gerer ce bug


Nous affichons le contenu d'un registre en Hexa et nous avons respecter la convention Big edian 
du processeur Mips.
