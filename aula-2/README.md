# Aula 2:
### Lição 2:
> Escreva as classes SERVER e CLIENT com métodos sendBytes e receiveBytes e inclua função testaBytes dentro do arquivo projeto.hpp de modo que os programas server6b.cpp e client6b.cpp funcionem corretamente. Mostre server6b/client6b funcionando.
> 
> **Saída esperada:**
>
>```
>pi@raspberrypi ~/labinteg/projeto/camserver $ server6b
>server: got connection from 192.168.0.109
>Recebeu corretamente 100000 bytes 214
>usuario@computador ~/labinteg/projeto/camserver $ client6b 192.168.0.110
>client: connecting to 192.168.0.110
>Recebeu corretamente 100000 bytes 111
>Erro na recepcao de 100000 bytes 2
>```

### Lição 2:
> Usando os novos métodos, faça os seguintes programas funcionarem. Mostre no vídeo que seu server6c/client6c funcionam. Mostre que você usou as funções ntohl e htonl.
> (Programas server6c.cpp e client6c.cpp)

### Lição 3:
> Usando os novos métodos e a função testaVb abaixo (a ser incluída no projeto.hpp), mostre que os programas server8/client8 funcionam
>``` cpp
>bool testaVb(const vector<BYTE> vb, BYTE b) {
>   //Testa se todos os bytes de vb possuem valor b
>   bool igual=true;
>   for (unsigned i=0; i<vb.size(); i++)
>      if (vb[i]!=b) { igual=false; break; }
>   return igual;
>}
>```