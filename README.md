# Electronic Voting Simulation - English

This project is a simulation of an electronic voting machine developed in C, using the `graphics.h` library. The simulation replicates the basic functionality of a voting machine, allowing votes to be registered and counted like a real voting process.

## Prerequisites

To compile and run this project on your computer, you need to follow some steps to install the GCC compiler and the `graphics.h` library.

### 1. Installing GCC

1. Visit the [TDM-GCC](https://jmeubank.github.io/tdm-gcc/) website and download the GCC compiler.
2. Run the TDM-GCC installer.
3. **Uncheck** the checkbox on the initial screen and click **Create**.
4. Choose the installation location and proceed with the installation.

### 2. Installing the `graphics.h` Library

1. Download `graphics.h` and `winbgim.h` from the following repository: [Graphics Library](https://github.com/SagarGaniga/Graphics-Library/tree/master).
2. Copy the `graphics.h` and `winbgim.h` files to the `include` folder inside the GCC installation directory.
3. Download the `libbgi.a` file and place it in the `lib` folder of the same directory.

### 3. Configuration in Code::Blocks

1. Install [Code::Blocks](https://www.codeblocks.org/).
2. In Code::Blocks, go to **Settings > Compiler**.
3. In **Toolchain Executables**, select the directory where TDM-GCC was installed.
4. Go to **Linker settings > Other linker options** and add the following options:

   ```
   -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
   ```

## How to Run

1. Open the `urna.cpp` file in Code::Blocks.
2. Compile and run the project.

To finalize the simulation, a total of 6 votes must be registered. The CPFs (Brazilian ID numbers) allowed for voting are already pre-registered in the machine, simulating a real voting process. The valid CPFs are:

- 105.481.020-66
- 625.461.080-93
- 226.910.130-81
- 842.465.760-85
- 979.343.010-90

## Ready-to-Use Executable

If you don't want to compile the code, the executable is already available in the repository after cloning.

## Contributions

Contributions are welcome! Feel free to open issues or submit pull requests to improve the project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

_________________________________________________

# Simulação de Votação Eletrônica - Português

Este projeto é uma simulação de uma urna eletrônica desenvolvida em C, utilizando a biblioteca `graphics.h`. A simulação replica a funcionalidade básica de uma urna de votação, permitindo que votos sejam registrados e contados de forma semelhante a um processo de votação real.

## Pré-requisitos

Para compilar e executar este projeto em seu computador, siga os passos para instalar o compilador GCC e a biblioteca `graphics.h`.

### 1. Instalando o GCC

1. Visite o site [TDM-GCC](https://jmeubank.github.io/tdm-gcc/) e baixe o compilador GCC.
2. Execute o instalador do TDM-GCC.
3. **Desmarque** a caixa de seleção na tela inicial e clique em **Criar**.
4. Escolha o local de instalação e prossiga com a instalação.

### 2. Instalando a Biblioteca `graphics.h`

1. Baixe `graphics.h` e `winbgim.h` do repositório a seguir: [Graphics Library](https://github.com/SagarGaniga/Graphics-Library/tree/master).
2. Copie os arquivos `graphics.h` e `winbgim.h` para a pasta `include` dentro do diretório de instalação do GCC.
3. Baixe o arquivo `libbgi.a` e coloque-o na pasta `lib` do mesmo diretório.

### 3. Configuração no Code::Blocks

1. Instale o [Code::Blocks](https://www.codeblocks.org/).
2. No Code::Blocks, vá para **Configurações > Compilador**.
3. Em **Executáveis do Toolchain**, selecione o diretório onde o TDM-GCC foi instalado.
4. Vá para **Configurações do Linker > Outras opções de link** e adicione as seguintes opções:

   ```
   -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32
   ```

## Como Executar

1. Abra o arquivo `urna.cpp` no Code::Blocks.
2. Compile e execute o projeto.

Para finalizar a simulação, um total de 6 votos deve ser registrado. Os CPFs (números de identificação brasileiros) permitidos para votação já estão pré-cadastrados na urna, simulando um processo de votação real. Os CPFs válidos são:

- 105.481.020-66
- 625.461.080-93
- 226.910.130-81
- 842.465.760-85
- 979.343.010-90

## Executável Pronto para Uso

Se você não deseja compilar o código, o executável já está disponível no repositório após o clone.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou enviar pull requests para melhorar o projeto.

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.
