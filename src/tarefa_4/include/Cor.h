#ifndef COR_H
#define COR_H

class Cor {
    public:
        float r;
        float g; 
        float b;

        Cor(float r, float g, float b);

        Cor somarCor(Cor& c);
        Cor multiEscalar(float t);
        Cor multiComponente(Cor& c);

        void limitar();
        
        void escreverNoBuffer(unsigned char* pixel);
    };

#endif