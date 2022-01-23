![feup logo](feup_logo.png)
---

## Licenciatura em Engenharia Informática e Computação

---
# Redes de Computadores - Segundo Trabalho Laboratorial

## Índice

# Table of Contents 

- [Introdução](#introducao)
- [Arquitetura](#arquitetura)
- [Experiências](#experiencias)
    -  [Experiência 1](experiencia_1)
    -  [Experiência 2](experiencia_2)
    -  [Experiência 3](experiencia_3)
    -  [Experiência 4](experiencia_4)
- [Conclusão](#conclusao)


## Introdução

Este trabalho foi realizado no âmbito da cadeira de Redes de Computadores. O trabalho teve dois objetivos principais, o primeiro for o desenvolvimento de uma aplicação de download com FTP e o segundo objetivo foi a configuração de uma rede que seria utilizada para testar a aplicação. A configuração desta mesma rede consistiu configurar um router e um switch CISCO bem como as rotas nos diversos PC pertencentes a essa rede.

## Arquitetura

A nossa aplicação de download FTP tem como base uma arquitetura monolitica composta por 3 packages: 

### `api` 

que contem a logica para realizar downloads no modo `passive` a partir de metodos que obteem a informacao do cliente, bem como o seu ip e port, efetuam uma coneccao e descarregam o ficheiro; 

### `lib`

onde vivem as macros e a definicao dos tipos, bem como helper methods uteis em varias seccoes do projeto; 

### `middleware`

este package serve como camada de ligacao entre a nossa API e a API do servidor nela existem dois diretorios: `auth` que funciona como camada de autenticacao e autorizacao; e `connection` que contem as funcoes que estabelecem e terminam uma nova ligacao, enviam pedidos e recebem respostas. 

#### Utilizacao:

`$ ftp://[<user>:<password>@]<host>/<url-path> -[mode]`
  
*Options:*
-A: Active mode
-P: Passive mode

*Example:* 

`$ ./download ftp://ftp.up.pt/pub/kodi/timestamp.txt -A`

*Note:* The server is in the lab, to access it you need to be connected through the FEUP VPN.

## Experiências

### Experiência 1

Nesta experiência foi nos pedido para connectar 2 dois PC usando um switch e configurando os IP address de ambos. As perguntas que nos foram feitas para responder foram as seguintes:

1) O que é que são ARP packets e para que servem?

    ARP(Address Resolution Packets) como o próprio nome indica serve para resolver endereços na camada de ligação. Também serve para mapear um endereço IPv4 a um endereço físico com endereço MAC ou Ethernet.

2) Quais são os MAC e IP addresses do ARP packets e porquẽ?

    No caso do tux 4 os MAC e IP addresses do ARP packets são:

        - IP : 172.16.30.254
        - MAC : 00:21:5a:5a:7d:74

    No caso do tux 3 os MAC e IP addresses do ARP packets são:

        - IP: 172.16.30.1
        - MAC: 00:21:5a:61:24:92

    Quando damos ping de um tux para o outro o tux inicialmente manda um request para o IP especificado no qual quer saber o MAC address dessa mesma máquina. Por sua vez o tux a qual foi feito o pedido responde com um packet ARP no qual indica qual o MAC address requesitado que irá depois ser guardado em cache.

3) Que tipo de packets é que o comando ping gera?

    Inicialmente gera pacotes de ARP e em seguida gera packotes ICMP(Internet Control Message Protocol).

4) Quais os MAC e IP address dos packets gerados pelo ping?

    Os IP e MAC addresses gerados pelo ping request:

        - MAC e IP Origem: Tux que realizou o comando ping
        - MAC e IP Destino: O Tux alvo do pedido

    Os IP e MAC addresses gerados pelo ping response:

        - MAC e IP Origem: O Tux que recebeu o request
        - MAC e IP Destino: O Tux que iniciou o request

5) Como determinar se uma Ethernet frame is ARP,IP,ICMP ?

    Para determinar se um Ethernet Frame é ARP,IP,ICMP é nessário inspecionar o cabeçalho da Frame.

6) Como determinar o tamanho de uma frame recebida?

    Usando o wireshark é possível determinar o tamanho de packet inspecionado-o.

7) Qual o loopback interface e porque é que é importante?

    A interface de loopback permite ao computador fazer testes de diagnóstico da infraestrutura de transmissão e de transporte, isto é usada para confirmar se a carta de rede está configurada corretamente.

### Experiência 2

O objetivo desta experiência foi configurar 2 VLANs na Switch. Para isso foi nos pedidos para responder ás seguintes perguntas:

1) Como configurar a vlan30?

    Para configurar a vlan30 é necessário:

    - Criar a VLAN 30 no Switch
    
    ```bash=
    >configure terminal
        >vlan 30
        >end
    ```

    - Associar as portas que o Tux3 e do Tux4 estão ligados no switch á Vlan 30, neste caso o Tux 3 está associado á porta de 2 e o Tux 4 está associado á porta 1. 

    ```bash=
    >configure terminal
        >interface fastethernet 0/1
        >switchport mode access
        >switchport access vlan 30
        >end

    >configure terminal
        >interface fastethernet 0/2
        >switchport mode access
        >switchport access vlan 30
        >end
    ```

2) Quantos broadcast domains existem? Como conseguimos concluir a partir dos logs?

    O tux 3 e o tux 4 quando dão ping eles recebem packets um do outro mas não recebem nenhum packet do tux 2 e o tux 2 não recebe nenhum packet do tux 3 e do tux 4. Por isso podemos concluir que existem 2 broadcast domains um com o tux 2 e outro com o tux 3 e o tux 4.

### Experiência 3

Nesta experiência foi nos pedido para analisar um ficheiro de configuração de um Router, testar entradas de DNS e configurar rotas numa máquina local. Para isso foi nos pedido para responder ás seguintes perguntas:

1) Como configurar a rota estática num router comercial?

    Para configurar a rota estática num router comercial é necessário, correr os seguintes comandos na consola do router:

    ```bash=
    > configure terminal
        > ip route [destino] [máscara] [gateway]
        > exit
    ```

2) Como configurar o NAT num router comercial?

    Para configurar o NAT num router comercial é necessário correr os seguintes comandos na consola do router:

    ```bash=
    conf t 
        interface gigabitethernet 0/0 * 
            ip address 172.16.y1.254 255.255.255.0 
            no shutdown 
            ip nat inside 
            exit 
        interface gigabitethernet 0/1* 
            ip address 172.16.1.y9 255.255.255.0 
            no shutdown 
            ip nat outside 
            exit 
        ip nat pool ovrld 172.16.1.y9 172.16.1.y9 prefix 24 
        ip nat inside source list 1 pool ovrld overload 
        access-list 1 permit 172.16.y0.0 0.0.0.7 
        access-list 1 permit 172.16.y1.0 0.0.0.7 
        ip route 0.0.0.0 0.0.0.0 172.16.1.254 
        ip route 172.16.y0.0 255.255.255.0 172.16.y1.253 
        end
    ```


3) O que é que faz o NAT?

    O NAT(Network Address Translation) é uma técnica que permite reescrever os endereços de IP de origem de forma a que um computador numa rede interna tenha acesso ao exterior, isto é o router faz a tradução de endereços IP não registados possam aceder à Internet ou rede pública. 

4) Como configurar o serviço de DNS no host?

    Para configurar o serviço de DNS no host é necessário alterar o ficheiro etc/resolv.conf no caso desta experiência foi adicionado :

    ```bash=
    nameserver 9.9.9.9
    ```

5) Que pacotes são trocados pelo DNS e que informação transportam?

    Numa fase inicial o host manda um packet a perguntar qual o IP de do hostname desejado, em seguida deve receber uma resposta do servidor com IP do hostname.

6) Que packets ICMP são observados e porquê?

    São observados packets ICMP de request/reply uma vez que adicionada um rota o computador deve ser capaz de contactar com a rota adicionada. Se não é enviado Host Unreachable .
    
7) Quais os IP e MAC addresses associados ao ICMP e porquê?

    Os IP e MAC addresses associados são os IP e MAC addresses do computador que realiza o request e o destino para o request é feito (Isto é o IP e o MAC do hostname adicionado).

8) Que rotas existiam na maquina? Qual o seu significado?

    Na tabela de rotas apenas existia a default gateway do computador, que serve de ponto de acesso a outras redes.


### Experiência 4

Nesta experiência foi a aplicação da configuração testada na experiência 3 com base na experiência 2, isto é configuração do Switch e do Router. Para isso foi nos pedido para responder ás seguintes perguntas:

1) Que rotas estavam nos Tuxes e o que é que significam?



2) Que informação uma entrada da fowarding table contêm?

3) Que mensagens ARP e MAC addresses associados são observados e porquê?

4) Quais os IP e MAC addresses associados a ICMP packets e porquê?

5) Quais os caminhos seguidos pelos packets nas experiências realizadas e porquê?



## Conclusão

Este trabalho alcançou os dois objetivos principais, com a aplicação de download com FTP e a configuração de uma rede para testar a aplicação.

O cliente FTP foi implementado com sucesso, e é capaz de transferir diferentes ficheiros com tamanhos diferentes. Com o desenvolvimento deste programa, nós percebemos melhor este protocolo e como um protocolo oficial funciona, comparando com o que foi feito.

A configuração da rede foi concluída com sucesso. Permitiu-nos perceber, num nível mais aprofundado, como uma rede funciona.

Os objetivos dos guiões laboratoriais foram atingidos, e deixou-nos com uma perspetiva diferente do funcionamento de como as redes de computadores funcionam.
