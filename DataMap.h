#ifndef _DATAMAP_H_
#define _DATAMAP_H_

class DataMap{

    public:

        DataMap(int lvl, int l, int h, int m){
            level = lvl;
            largeur = l;
            hauteur = h;
            mines = m;

            useThirdMark = false;
            useBlackCases = false;
            useBounds = true;
        }

        DataMap(int lvl, int l, int h, int m, bool useTM, bool useBC, bool useB){
            level = lvl;
            largeur = l;
            hauteur = h;
            mines = m;

            useThirdMark = useTM;
            useBlackCases = useBC;
            useBounds = useB;
        }

        int level;
        int largeur;
        int hauteur;
        int mines;

        int nbCasesRest;
        int nbMinesRest;

        bool useFlag;
        bool useThirdMark;
        bool useBlackCases;
        bool useBounds;
};

#endif
