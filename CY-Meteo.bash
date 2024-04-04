#!/bin/bash

# Déclaration des variables

w=0 #vent
h=0 #altitude
m=0 #humidite
t=0 #temperature
p=0 #pression

f=0 #fichier
d=0 #date
l=0 #lieu

h=0 #latitude
g=0 #longitude

typeDonnee=0 # Determine si l'utilisateur entre une option. Par défaut 0 option.
tri='avl' # Le choix du tri n'est pas obligatoire





fichier_entree=''

NUM_CHAMP_STATION='1'
NUM_CHAMP_DATE='2'
# NUM_CHAMP_PRESSION_MER='3'
NUM_CHAMP_DIRECTION_VENT='4'
NUM_CHAMP_VITESSE_VENT='5'
NUM_CHAMP_HUMIDITE='6'
NUM_CHAMP_PRESSION_STATION='7'
# NUM_CHAMP_VARIATION_PRESSION='8'
# NUM_CHAMP_PRECIPITATIONS='9'
NUM_CHAMP_COORDONEES='10'
NUM_CHAMP_TEMPERATURE='11'
# NUM_CHAMP_TEMPERATURE_MIN='12'
# NUM_CHAMP_TEMPERATURE_MAX='13'
NUM_CHAMP_ALTITUDE='14'
# NUM_CHAMP_COMMUNES='15'

FICHIER_F_ALTITUDE='data/filtre_altitude.csv'
FICHIER_F_HUMIDITE='data/filtre_humidite.csv'
FICHIER_F_VENT='data/filtre_vent.csv'
FICHIER_F_p1='data/filtre_p1.csv'
FICHIER_F_p2='data/filtre_p2.csv'
FICHIER_F_p3='data/filtre_p3.csv'
FICHIER_F_t1='data/filtre_t1.csv'
FICHIER_F_t2='data/filtre_t2.csv'
FICHIER_F_t3='data/filtre_t3.csv'

FICHIER_T_altitude='data/tri_altitude.csv'
FICHIER_T_humidite='data/tri_humidite.csv'
FICHIER_T_vent='data/tri_vent.csv'
FICHIER_T_p1='data/tri_p1.csv'
FICHIER_T_p2='data/tri_p2.csv'
FICHIER_T_p3='data/tri_p3.csv'
FICHIER_T_t1='data/tri_t1.csv'
FICHIER_T_t2='data/tri_t2.csv'
FICHIER_T_t3='data/tri_t3.csv'

# Fonction optlieu qui gere les options geographiques

# optlieu $option
optlieu() {
    # si on a deja une option de lieu, on quitte
    if (($arg_lieu != 0)) ; then 
        echo "Erreur option -$1 : l'option de lieu doit etre unique"
        return 1
    fi
    arg_lieu=1
    # lieu=$1
    return 0
}

# Utilisation des regex pour le filtrage géographique

regex=""
REGEX_FRANCE="([0-8][0-9]|9[0-5]|2[a,b,A,B])[0-9]{3}$"
REGEX_GUYANE="973[0-9]{2}$"
REGEX_SAINT_PIERRE="975[0-9]{2}$"
REGEX_ANTILLES="97[1-2,7-8][0-9]{2}$"
REGEX_OCEAN_INDIEN="97[4,6][0-9]{2}$"
REGEX_ANTARCTIQUE="98414$"

# Traitement des options de ligne de commande
while getopts ":d:t:p:fwhmFGQSAO:-:" option; do
    if [ "$option" = '-' ] ; then
        case $OPTARG in
            # Options de tris
            avl)
                tri=$OPTARG ;;
            abr)
                tri=$OPTARG ;;
            tab)
                tri=$OPTARG ;;

            # Options manuel commande
            help)
                echo "Manuel d'utilisation :
./Projet-Meteo.sh -f [FICHIER] [TYPE de données] [TRIS] [LIEUX] [DATE]

-f<fichier> : fichier d’entrée, option obligatoire et unique

[Type de données]
-t<mode> : température
-p<mode> : pression atmosphérique 
-w : vent
-h : altitude
-m : humidité

<mode> :
-1 (minimales, maximales et moyennes par station dans l'ordre croissant du num station)
-2 (moyennes par date/heure, triées dans l’ordre chronologique)
-3 (par date/heure, triées ordre chronologique puis par ordre croissant id station)

[TRIS]
--tab : tri par listes chainées 
--abr : tri par ABR
--avl : tri par AVL

[LIEUX]
-F : France : France métropolitaine + Corse
-G : Guyane française
-S : Saint-Pierre et Miquelon
-A : Antilles
-O : Océan indien
-Q : Antarctique
Les options de lieux sont exclusives entre elles.

[DATE]
-d<min,max> : dates dans l’intervalle de dates [<min>...<max>] au format YYYY-MM-DD, option unique
";;
            *)  echo "Erreur option invalide : $OPTARG"
                exit 1 ;;
        esac
    else
        case "$option" in
            # Options de données
            w)
                w=1 
                typeDonnee=1 ;;
            h)
                h=1
                typeDonnee=1 ;;
            m)
                m=1 
                typeDonnee=1 ;;
            t)
                if (($OPTARG < 1)) || (($OPTARG > 3)) ; then
                    echo "Erreur : le mode de température est compris entre 1 et 3"
                    exit 1
                fi
                t=$OPTARG 
                typeDonnee=1 ;;
            p)
                if (($OPTARG < 1)) || (($OPTARG > 3)) ; then
                    echo "Erreur : le mode de pression est compris entre 1 et 3"
                    exit 1
                fi
                p=$OPTARG 
                typeDonnee=1 ;;
            

            # Options de fichier
            f)
             
            if (( $f != 0 )) ; then
                echo "Erreur : l'option -f doit etre unique"
                exit 1
            fi
            fichier_entree="$OPTARG"
            if [ ! -f "$fichier_entree" ] ; then
                echo "Erreur : '$fichier_entree' n'existe pas ou n'est pas un fichier"
                exit 1
            fi
            f=1
            ;;


            # Options de lieu
            F) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_FRANCE" ;;
            G) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_GUYANE" ;;
            S) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_SAINT_PIERRE" ;;
            A) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_ANTILLES" ;;
            O) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_OCEAN_INDIEN" ;;
            Q) 
            if ! optlieu "$option" ; then
                exit 1
            fi 
            regex="$REGEX_ANTARCTIQUE" ;;


            # Autre
            --) 
            break;;

            # Options de date
            d) 
            if (($d != 0)) ; then
                echo "Erreur : l'option de date doit etre unique"
                exit 1
            fi
            date=$OPTARG 
            # echo "Dates : $OPTARG"
            d=1 ;;

            *)
             echo "Erreur option invalide : $OPTARG"
                exit 1 ;;
        esac
    fi   
done

# Verification de la presence des options obligatoires

if (( $typeDonnee != 1 )) ; then
    echo "Erreur : veuillez preciser au moins une option de type de donnee"
    echo "$typeDonnee"
    exit 1
elif (( $f != 1 )) ; then
    echo "Erreur : pas de fichier d'entree, utilisez l'option -f <fichier> pour inclure un fichier d'entree"
    exit 1
fi

# Commandes de filtrage

echo "Filtrage du fichier d'entrée"



# Filtrage selon le type de donnee

# Altitude 
if (($h > 0)) ; then
    # filtrage avec restriction geographique
    if (($l == 1)) ; then
        # On prend d'abord les bonnes lignes, puis on filtre par colonne
        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_ALTITUDE"
    # filtrage sans restiction geographique
    else 
        # On filtre par colonne, et on enleve la premiere ligne avec les titres
        cut -sd\; -f"$NUM_CHAMP_ALTITUDE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_ALTITUDE"
    fi
fi



# Humidite

if (($m > 0)) ; then

    if (($l == 1)) ; then

        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_HUMIDITE"
    else
        cut -sd\; -f"$NUM_CHAMP_HUMIDITE","$NUM_CHAMP_STATION","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_HUMIDITE"
    fi
fi



# Vent

if (($w > 0)) ; then

    if (($l == 1)) ; then

        grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT","$NUM_CHAMP_COORDONEES" > "$FICHIER_F_VENT"
    else 
        cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DIRECTION_VENT","$NUM_CHAMP_VITESSE_VENT","$NUM_CHAMP_COORDONEES" "$fichier_entree" | tail -n+2 > "$FICHIER_F_VENT"
    fi
fi

# Pression

if (($p > 0)) ; then

    # Mode 1
    if (($p == 1)) ; then

        if (($l == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p1"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" | tail -n+2 > "$FICHIER_F_p1"
        fi    
    # Mode 2
    elif (($p == 2)) ; then 
        
        if (($l == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p2"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" "$fichier_entree" | tail -n+2 > "$FICHIER_F_p2"
        fi    
    
    # Mode 3
    else 

        if (($l == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_PRESSION_STATION" > "$FICHIER_F_p3"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_DATE","$NUM_CHAMP_PRESSION_STATION" | tail -n+2 "$fichier_entree" > "$FICHIER_F_p3"
        fi
        
    fi
fi

# Temperature

if (($t > 0)) ; then

    # Mode 1
    if (($t == 1)) ; then

        if (($l == 1)) ; then
            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t1"
        else 
            cut -sd\; -f"$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t1"
        fi

    # Mode 2
    elif (($t == 2)) ; then 

        if (($l == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t2"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t2"
        fi

    # Mode 3
    else 

        if (($l == 1)) ; then

            grep -E "$regex" "$fichier_entree" | cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" > "$FICHIER_F_t3"
        else 
            cut -sd\; -f"$NUM_CHAMP_DATE","$NUM_CHAMP_STATION","$NUM_CHAMP_TEMPERATURE" "$fichier_entree" | tail -n+2 > "$FICHIER_F_t3"
        fi
        
    fi
fi

if (($arg_date > 0)) ; then
    # echo "separation des dates"
    #echo "$date"
    date1=${date%%,*} # Je recupère la première date
    #echo "première date : $date1"
    date2=${date##*,} # Je recupère la seconde date
    #echo "seconde date : $date2"
    echo "$date1">data/date1
    echo "$date2">data/date2
    verif=$(grep -E "$REGEX_DATE" data/date1)
    #echo "la verification vaut : $verif"
    if [ "$verif" != "$date1" ] ; then
        echo "La première date n'est pas au bon format (format : AAAA-MM-JJ)"
        exit 1
    fi
    verif=$(grep -E "$REGEX_DATE" data/date2)
    if [ "$verif" != "$date2" ] ; then
        echo "La seconde date n'est pas au bon format (format : AAAA-MM-JJ)"
        exit 1
    fi
    rm data/date1 data/date2
fi

echo "Filtrage des fichiers terminé"
echo "Tri des fichiers filtrés en cours"


# Verification de l'existence du fichier executable de tri

if [ ! -x 'bin/tri' ] ; then
    echo "Compilation du fichier executable de tri"
    make all
    retour_makefile="$?"
    if (($retour_makefile != 0)) ; then
        echo "Erreur makefile : code $retour_makefile"
        make mrproper
        exit 1
    fi
    make clean
fi



# Tri des fichiers filtres et construction des graphiques de sortie

# Altitude

if (($arg_altitude == 1)) ; then
    # Execution du programme    
    ./bin/tri -rf "$FICHIER_F_ALTITUDE" -o "$FICHIER_T_altitude" -t "$tri" -k h

    # Verification du code de retour du programme de tri
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi

    # Creation du graphique final
    cd 'gnuplot'
    gnuplot "altitude.plt"
    cd '..'

    # Suppression des fichiers temporaires
    rm "$FICHIER_F_ALTITUDE" "$FICHIER_T_altitude"
fi

# Humidite

if (($arg_humidite == 1)) ; then
    ./bin/tri -f "$FICHIER_F_HUMIDITE" -o "$FICHIER_T_humidite" -t "$tri" -k m 
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi
    cd 'gnuplot'
    gnuplot "humidite.plt"
    cd '..'
    rm "$FICHIER_F_HUMIDITE" "$FICHIER_T_humidite"
fi

# Vent

if (($arg_vent == 1)) ; then
    ./bin/tri -f "$FICHIER_F_VENT" -o "$FICHIER_T_vent" -t "$tri" -k w
    retour_C="$?"
    if (($retour_C != 0)) ; then
        echo "Erreur d'exécution de bin/tri, code $retour_C"
        exit 1
    fi
    cd 'gnuplot'
    gnuplot "vent.plt"
    cd '..'
    rm "$FICHIER_F_VENT" "$FICHIER_T_vent"
fi

# Pression

if (($arg_pression > 0)) ; then
    # Mode 1
    if (($arg_pression == 1)) ; then

        ./bin/tri -t "$tri" -f "$FICHIER_F_p1" -o "$FICHIER_T_p1" -k p1
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p1.plt'
        cd '..'
        rm "$FICHIER_F_p1" "$FICHIER_T_p1"
    # Mode 2
    elif (($arg_pression == 2)) ; then

        ./bin/tri -f "$FICHIER_F_p2" -o "$FICHIER_T_p2" -t "$tri" -k p2
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p2.plt'
        cd '..'
        rm "$FICHIER_F_p2" "$FICHIER_T_p2"
    # Mode 3
    else

        ./bin/tri -f "$FICHIER_F_p3" -o "$FICHIER_T_p3" -t "$tri" -k p3
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 'p3.plt'
        cd '..'
        # rm "$FICHIER_F_p3" "$FICHIER_T_p3"
    fi
fi

# Temperature

if (($arg_temperature > 0)) ; then
    # Mode 1
    if (($arg_temperature == 1)) ; then

        ./bin/tri -f "$FICHIER_F_t1" -o "$FICHIER_T_t1" -t "$tri" -k t1
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't1.plt'
        cd '..'
        rm "$FICHIER_F_t1" "$FICHIER_T_t1"
    # Mode 2
    elif (($arg_temperature == 2)) ; then

        ./bin/tri -f "$FICHIER_F_t2" -o "$FICHIER_T_t2" -t "$tri" -k t2
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't2.plt'
        cd '..'
        rm "$FICHIER_F_t2" "$FICHIER_T_t2"
    # Mode 3
    else

        ./bin/tri -f "$FICHIER_F_t3" -o "$FICHIER_T_t3" -t "$tri" -k t3
        retour_C="$?"
        if (($retour_C != 0)) ; then
            echo "Erreur d'exécution de bin/tri, code $retour_C"
            exit 1
        fi
        cd 'gnuplot'
        gnuplot 't3.plt'
        cd '..'
        # rm "$FICHIER_F_t3" "$FICHIER_T_t3"
    fi
fi

echo "Tris terminés"
echo "Graphiques générés dans le répertoire data"

exit 0