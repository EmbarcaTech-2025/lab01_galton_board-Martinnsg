# 🎲 Galton Board com Raspberry Pi Pico W - EmbarcaTech 2025

**Autor:** Gabriel Martins  
**Curso:** Residência Tecnológica em Sistemas Embarcados  
**Instituição:** EmbarcaTech - HBr  
**Local:** Campinas, ___ de 2025

---

## 📌 Descrição do Projeto

Este projeto implementa uma versão digital de uma **Galton Board** utilizando a **Raspberry Pi Pico W**, simulando a queda de partículas entre pinos fixos e exibindo um histograma de distribuição no display **OLED SSD1306** via protocolo **I2C**. A simulação permite observar a formação da curva normal (distribuição Gaussiana) a partir de eventos aleatórios.

---

## 🧠 Funcionalidades

- Simulação visual da queda de partículas em uma Galton Board
- Desvio pseudoaleatório das partículas para esquerda ou direita
- Renderização gráfica de:
  - Pinos fixos
  - Partículas em movimento
  - Histograma de distribuição
  - Contador total de partículas
- Atualização em tempo real no display OLED

---

## 🗂️ Estrutura do Projeto

galton_board/
├── src/
│ ├── main.c
│ ├── ball_sim.c
│ ├── graphics.c
│ └── machine.c
├── include/
│ ├── ball_sim.h
│ ├── graphics.h
│ └── machine.h
├── CMakeLists.txt


---

## 🚀 Como Rodar

### ✅ Requisitos

- Raspberry Pi Pico W
- Display OLED SSD1306 (I2C)
- SDK da Raspberry Pi Pico instalado
- Toolchain arm-none-eabi

### 🔨 Compilação

```bash
mkdir build && cd build
cmake ..
make

📤 Upload do firmware

    Conecte o Pico W em modo BOOTSEL

    Copie o .uf2 gerado na pasta build/ para o dispositivo montado

🧪 Resultados Esperados

    As partículas aparecem uma a uma, caindo e se desviando nos pinos

    O histograma se forma dinamicamente na parte inferior da tela

    Um contador mostra o número total de partículas simuladas

    Os pinos são desenhados estaticamente no centro da tela

🛠️ Melhorias Futuras

    Controle via botão físico ou encoder rotativo

    Interface Web usando Wi-Fi (Pico W)

    Salvamento do histograma em memória persistente

    Modo de simulação com parâmetros ajustáveis

📜 Licença

Este projeto está licenciado sob os termos da MIT License. 