# Documentação PROJETO DETECCAO UMIDADE TEMPERATURA MINHOCARIO

## 1.	Introdução
A minhocultura é o nome que damos à criação de minhocas.  É simples e de baixo custo para agricultores e fácil para se conseguir os materiais que são necessários para utilizar na criação dos minhocários dentro das propriedades rurais (Formenton, 2005). 
Minhocários são espaços onde são criadas as minhocas. Eles não precisam de muito investimento, pois pode ser utilizado recursos da própria propriedade para construir o local e para alimentar as minhocas (Schiedeck et al, 2014). 
As minhocas se alimentam de matérias orgânicas como folhas, esterco, frutas, hortaliças e etc. Se alimentando destes materiais, as minhocas as transformam em húmus (Formenton, 2005; Schiedeck et al, 2014). 
Essas matérias orgânicas também são o substrato, ou seja, onde as minhocas vivem e se alimentam (Formenton, 2005; Schiedeck et al, 2014). Conforme estas matérias orgânicas vão se decompondo, elas liberam calor e gases. Por isso que se mede a temperatura e a umidade do substrato para que as minhocas não morram e nem fujam. 
Segundo Machado (2024), a temperatura ideal para o substrato deve ser entre 20°C e 25°C e a umidade estar entre 60% a 70% para que as minhocas possam viver e se reproduzir.
Diante da necessidade de medir a temperatura e a umidade do substrato do minhocário, este projeto pretende criar um dispositivo e um aplicativo móvel para este fim. Este dispositivo será feito com o uso de Arduíno e conterá 2 sensores para captar a temperatura e a umidade.
O Arduíno é uma placa que contém o hardware, o software e a IDE - local onde você insere os comandos para o Arduíno executar a programação. Ele também é um código livre (ou aberto) para que todos possam utilizar, tais como programadores, designers, pesquisadores, e outros interessados em criar novos projetos (Mota, 2015).
Neste projeto, o Arduíno será utilizado para capturar as informações sobre a temperatura e umidade do minhocário através dos sensores. Os dados capturados serão transferidos para a memória da placa, onde serão processados, e as informações serão enviadas via bluetooth para celular. 
Esse acompanhamento dos índices de temperatura e umidade é importante para o produtor rural poder acompanhar o minhocário e garantir a qualidade de vida das minhocas, melhorando a produção de humus. 

## 2.	Objetivo geral
Desenvolver dispositivo eletrônico para detecção dos índices de umidade e temperatura do substrato do minhocário. 

## 3.	Objetivos específicos
- desenvolver um dispositivo eletrônico para detecção de umidade 
- desenvolver um dispositivo eletrônico para detecção de temperatura

## 4.	Metodologia
Esta pesquisa se caracteriza como experimental. As pesquisas experimentais são aquelas que manipulam o objeto para controlar os elementos que o compõem (Tumelero, 2019).  Nesta pesquisa, o objeto é o substrato do minhocário e os elementos que serão controlados serão a temperatura e a umidade. Para isso, criaremos e testaremos o uso do dispositivo de temperatura e umidade para o controle do substrato do minhocário. 
Para a construção deste dispositivo será utilizada uma placa de Arduino Uno, sensores de temperatura e umidade, atuadores Buzzer (dispositivos que transmitem sons), e LEDs para transmitir a cor vermelha para solo seco, verde para situação ideal e azul para muita umidade. 
As informações coletadas pelo dispositivo serão enviadas para o celular do produtor rural via Bluetooth para o aplicativo Serial Bluetooth Terminal, que é aberto para uso geral. 
Esta pesquisa se caracteriza como experimental. As pesquisas experimentais são aquelas que manipulam o objeto para controlar os elementos que o compõem (Tumelero, 2019).  Nesta pesquisa, o objeto é o substrato do minhocário e os elementos que serão controlados serão a temperatura e a umidade. Para isso, criaremos e testaremos o uso do dispositivo de temperatura e umidade para o controle do substrato do minhocário. 
Para a construção deste dispositivo será utilizada uma placa de Arduino Uno, sensores de temperatura e umidade, atuadores Buzzer (dispositivos que transmitem sons), e LEDs para transmitir a cor vermelha para solo seco, verde para situação ideal e azul para muita umidade. 
As informações coletadas pelo dispositivo serão enviadas para o celular do produtor rural via Bluetooth para o aplicativo Serial Bluetooth Terminal, que é aberto para uso geral. 

## 5.	Resultados esperados 
Esperamos que o dispositivo desenvolvido atenda as necessidades dos produtores rurais que possuem ou querem construir minhocários e produzir humus. 

## 6.	Referências
MOTA, A. D. Apostila Arduíno Básico, Vol 1. Serra: Vida de Silício, 2015.
SCHIEDECK, Gustavo et al. Minhocultura: produção de humus. 2. ed. Brasília: Embrapa, 2014. 56 p. Disponível em: https://ainfo.cnptia.embrapa.br/digital/bitstream/item/128305/1/ABC-Minhocultura-ed02-2014.pdf. Acesso em: 01 out. 2024.
TUMELERO, N. Pesquisa experimental: o que é e como fazer em 5 passos. Disponível em: <https://blog.mettzer.com/pesquisa-experimental/>.

