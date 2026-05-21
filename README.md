# LAB 23 - JNIDefenseDemo

## Présentation

JNIDefenseDemo est une application Android pédagogique développée avec JNI (Java Native Interface) et C++.  
Ce laboratoire montre comment intégrer une petite couche défensive native dans une application Android afin de détecter certains comportements suspects comme :

- le debug ;
- l’instrumentation ;
- la présence de bibliothèques potentiellement utilisées pour l’analyse dynamique.

Le projet combine :

- Java ;
- JNI ;
- C++ ;
- Android NDK ;
- CMake ;
- Logcat.

L’objectif principal est pédagogique : comprendre comment une application Android peut déplacer certains contrôles sensibles dans une bibliothèque native.

---

# Objectifs du laboratoire

Ce laboratoire permet de comprendre :

- l’intégration JNI dans Android ;
- la communication Java ↔ C++ ;
- la compilation native avec CMake ;
- le chargement d’une bibliothèque `.so` ;
- la journalisation native avec Logcat ;
- l’implémentation de contrôles défensifs simples ;
- l’adaptation de l’interface selon l’état détecté.

---

# Fonctionnement général

L’application suit le flux suivant :

```text
MainActivity
    ↓
isDebugDetected()
    ↓
Bibliothèque native C++
    ↓
Contrôles défensifs
    ↓
Retour booléen vers Java
    ↓
Mise à jour de l’interface
```

---

# Contrôles implémentés

## 1. Détection simple de debug

L’application utilise un contrôle basé sur :

```cpp
ptrace(PTRACE_TRACEME, ...)
```

afin de détecter un environnement potentiellement supervisé.

---

## 2. Inspection de `/proc/self/maps`

Le programme inspecte les bibliothèques chargées en mémoire et recherche certaines signatures textuelles comme :

- frida
- xposed
- gdbserver
- magisk

---

# Structure du projet

```text
app/
 └── src/
      └── main/
           ├── java/com/example/jnidefensedemo/
           │     └── MainActivity.java
           │
           ├── cpp/
           │     ├── native-lib.cpp
           │     └── CMakeLists.txt
           │
           ├── res/layout/
           │     └── activity_main.xml
           │
           └── AndroidManifest.xml
```

---

# Technologies utilisées

- Android Studio
- Java
- C++
- JNI
- Android NDK
- CMake
- Logcat

---

# Interface de l’application

## Cas normal

L’application affiche :

```text
Etat securite : OK
Hello from C++ via JNI !
Factoriel de 10 = 3628800
```

---

## Cas suspect

L’application affiche :

```text
Etat securite : environnement suspect detecte
Fonctions natives desactivees
Calcul natif bloque
```

---

# Logs Logcat

Filtre utilisé :

```text
ANTI_DEBUG
```

Exemples :

```text
Aucun trace/debug detecte via ptrace
Etat de securite : OK
```

ou :

```text
Etat suspect : trace/debug detecte
Etat de securite : environnement suspect detecte
```

---

# Compilation native

Le projet utilise :

- Android NDK
- CMake
- LLDB

La bibliothèque générée est :

```text
libnative-lib.so
```

---

# Démonstration pédagogique

Le laboratoire permet de comparer :

| Exécution normale | Exécution avec debug |
|---|---|
| Etat securite : OK | environnement suspect |
| fonctions JNI actives | fonctions JNI bloquées |
| calcul affiché | calcul désactivé |

---

# Vidéo Démonstrative



https://github.com/user-attachments/assets/46be0a21-9204-48e2-a505-cc9b8c86cb89



---

# Auteur

Ella Vanessa MUGISHA

1ère année — Génie Cyberdéfense et Systèmes de Télécommunications Embarquées  
ENSA Marrakech
