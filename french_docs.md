# Documentation de l'émulateur MIPS

## Vue d'ensemble
Ce document fournit une vue d'ensemble et une documentation détaillée de l'émulateur MIPS implémenté en C. L'émulateur simule l'architecture MIPS (Microprocesseur sans étages de pipeline verrouillés), couramment utilisée dans les contextes académiques à des fins pédagogiques.

Nous avons réussi à coder toutes les fonctions nécessaires à notre émulateur MIPS et nous les avons testées avec nos fichiers de tests. Notre émulateur fonctionne bien avec ces derniers. Cependant, il est nécessaire de connaître certains points importants concernant notre syntaxe :

- **Gestion des mnémoniques des noms de registres** : Nous avons pris en charge la mnémonique des noms des registres, permettant ainsi d'écrire `$zero` au lieu de `$0`. (Voir la fonction `checkRegisters` dans le module `Utility`).

- **Instructions nécessitant un offset ou un target** : Pour les instructions exigeant un offset ou un target, comme `JAL target`, `SW $2,offset($8)`, il est nécessaire que `offset` et `target` soient des multiples de 4.

- **Robustesse aux espaces dans les instructions MIPS** : Notre code est robuste aux espaces dans les instructions MIPS; on peut donc avoir `ADD    $4,$2   ,$5` comme `ADD $4,$2,$5`. (Voir la fonction `checkRegisters` dans le module `Utility`).

- **Affichage des états des registres** : Nous n'avons pas stocké les états des registres dans un fichier texte; nous les affichons dans la console.

- **Gestion des caractères blancs** : Nous avons pris en compte les caractères blancs que nous parvenons à identifier et à ignorer, à l'exception d'un seul qui nous pose problème. Nous ne le connaissons pas, mais il provoque des suppressions sur la ligne où il est placé. Nous avons effectué des recherches et demandé l'aide d'un professeur de TD, mais nous n'avons pas réussi à gérer ce bug.

- **Affichage du contenu d'un registre en Hexadécimal** : Nous affichons le contenu d'un registre en hexadécimal et avons respecté la convention Big Endian du processeur MIPS.

## Documentation des modules

### `main.c`
- **Description** : Initialise l'émulateur MIPS, y compris la configuration de la mémoire et des registres. Analyse les arguments de la ligne de commande et lance le processus d'exécution des instructions.
- **Fonctions principales** :
  - `main` : Le point d'entrée principal. Peut gérer les procédures d'initialisation et boucler sur le cycle d'exécution des instructions.

### `Function.c` et `Function.h`
- **Description** : Implémente les fonctionnalités d'instructions MIPS de base, telles que les opérations arithmétiques, les opérations logiques et les changements de flux de contrôle.
- **Fonctions principales** :
  - `executeInstruction` : Exécute une instruction MIPS donnée.
  - `arithmeticOp` : Effectue des opérations arithmétiques en fonction de l'opcode.
  - `logicOp` : Gère les opérations logiques.

### `HexaConverte.c` et `HexaConverte.h`
- **Description** : Facilite la conversion entre des chaînes hexadécimales et des valeurs numériques, essentielles pour la manipulation des adresses mémoire et des données.
- **Fonctions principales** :
  - `hexToString` : Convertit une valeur hexadécimale en une représentation en chaîne.
  - `stringToHex` : Convertit une représentation en chaîne d'un nombre hexadécimal en sa valeur numérique.

### `MemoryManagement.c` et `MemoryManagement.h`
- **Description** : Gère la mémoire simulée de l'environnement MIPS, y compris l'allocation, l'accès et la libération.
- **Fonctions principales** :
  - `allocateMemory` : Alloue de la mémoire pour la simulation MIPS.
  - `freeMemory` : Libère la mémoire allouée.
  - `readMemory` : Lit une valeur depuis une adresse mémoire spécifiée.
  - `writeMemory` : Écrit une valeur à une adresse mémoire spécifiée.

### `RegistryManagement.c` et `RegistryManagement.h`
- **Description** : Gère les registres MIPS, y compris les opérations de lecture et d'écriture dans les registres généraux et spéciaux.
- **Fonctions principales** :
  - `readRegister` : Lit une valeur depuis un registre spécifié.
  - `writeRegister` : Écrit une valeur dans un registre spécifié.

### `Utility.c` et `Utility.h`
- **Description** : Fournit un ensemble de fonctions utilitaires qui soutiennent le fonctionnement de l'émulateur.
- **Fonctions principales** :
  - `logError` : Enregistre un message d'erreur dans la console ou un fichier.
  - `bitwiseOperations` : Effectue des opérations binaires nécessaires aux instructions MIPS.
