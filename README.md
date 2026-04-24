# TPSE-I

Repositório da disciplina **TPSE I** com práticas de sistemas embarcados para a placa **BeagleBone Black**.

## Sobre o projeto

Este workspace reúne exercícios e práticas de programação em C com foco em:

- arquitetura ARM;
- manipulação de bits;
- processo de compilação cruzada (*cross-compilation*);
- organização de firmware para sistemas embarcados.

## Estrutura do repositório

```text
TPSE-I/
├── lab/
│   ├── run.txt
│   └── pratica_01/
│       ├── Makefile
│       ├── inc/
│       └── src/
├── revision/
│   ├── bitwise-programming/
│   │   ├── Makefile
│   │   └── src/
│   └── docs/
├── Exercises/
│   ├── bitwise-exercises/
│   └── pre-process-exercises/
└── toolchain/
    └── gcc-arm-none-eabi-10.3-2021.10/
```

## Pré-requisitos

- Linux (ou ambiente compatível com ferramentas GNU);
- `make`;
- toolchain ARM (`arm-none-eabi-gcc`), já incluída em `toolchain/`.

## Compilação

### Práticas principais

```bash
cd lab/
make
```

### Revisão de bitwise

```bash
cd revision/bitwise-programming
make
```
### Revisão de pré-processos

```bash
cd revision/Exercises/pre-process-exercises
make
```

Os binários e objetos gerados ficam, em geral, nas pastas `bin/` e `obj/` de cada módulo.

## Execução e testes

Consulte:

- `lab/run.txt` para orientações de execução no laboratório;
- os `Makefile` de cada pasta para alvos disponíveis (`make clean`, `make all`, etc.).

## Observações

- O projeto é voltado para fins didáticos.
- A estrutura pode crescer com novas práticas e exercícios ao longo do semestre.