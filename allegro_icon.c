#include <allegro.h>
/* XPM */
static const char *allegico_xpm[] = {
/* columns rows colors chars-per-pixel */
"64 64 105 2 ",
"   c #000000",
".  c #0B0101",
"X  c #0A0A0A",
"o  c #140000",
"O  c #1D0100",
"+  c #131313",
"@  c #1B1B1B",
"#  c #240100",
"$  c #320100",
"%  c #3A0201",
"&  c #232323",
"*  c #2C2C2C",
"=  c #323232",
"-  c #3B3B3B",
";  c #470301",
":  c #470806",
">  c #480907",
",  c #490E0C",
"<  c #5C0402",
"1  c #4A1311",
"2  c #4D1E1D",
"3  c #620502",
"4  c #6E0603",
"5  c #730703",
"6  c #7E0803",
"7  c #621412",
"8  c #532C2B",
"9  c #563232",
"0  c #444444",
"q  c #4B4B4B",
"w  c #555555",
"e  c #5B5B5B",
"r  c #624645",
"t  c #644948",
"y  c #735D5D",
"u  c #636363",
"i  c #6D6D6D",
"p  c #766161",
"a  c #796464",
"s  c #757575",
"d  c #7B7B7B",
"f  c #870C06",
"g  c #8C0A03",
"h  c #960B04",
"j  c #B00F06",
"k  c #B71006",
"l  c #B91006",
"z  c #AF1812",
"x  c #B83C39",
"c  c #C21206",
"v  c #C91307",
"b  c #C31308",
"n  c #D21407",
"m  c #DB1507",
"M  c #D71508",
"N  c #DB1508",
"B  c #E9080A",
"V  c #E51708",
"C  c #E5190C",
"Z  c #E51D13",
"A  c #E6251C",
"S  c #D6332F",
"D  c #E72C26",
"F  c #E82F29",
"G  c #816E6E",
"H  c #8B7A7A",
"J  c #AD7675",
"K  c #E94946",
"L  c #E94D4B",
"P  c #EA5755",
"I  c #E05E5C",
"U  c #E95B59",
"Y  c #D16D6B",
"T  c #838383",
"R  c #8C8C8C",
"E  c #939393",
"W  c #9E9090",
"Q  c #9B9B9B",
"!  c #A3A3A3",
"~  c #ACA0A0",
"^  c #ACACAC",
"/  c #B1A5A5",
"(  c #B6ABAB",
")  c #B5B4B4",
"_  c #BDB5B5",
"`  c #BABABA",
"'  c #ED8483",
"]  c #E68E8E",
"[  c #E39B9A",
"{  c #C1B6B5",
"}  c #C3C3C3",
"|  c #CCC2C2",
" . c #CDCDCD",
".. c #D4D4D4",
"X. c #DEDEDE",
"o. c #F4C6C6",
"O. c #E1D8D8",
"+. c #F0D4D4",
"@. c #E4E4E4",
"#. c #ECECEC",
"$. c #FBE4E4",
"%. c #FBE9E9",
"&. c #F4F4F4",
"*. c #FEF7F7",
"=. c #FEFEFE",
/* pixels */
"                                                                                                                                ",
"                                                                                                                                ",
"                                                                                                                =.=.=.=.        ",
"                                                                                                              =.=.=.=.=.=.      ",
"                                                                                                            =.=.=.=.=.=.=.      ",
"                                                                                                          =.=.=.=.=.=.=.        ",
"                                                                                                        =.=.=.=.=.=.=.          ",
"                                                                                                      =.=.=.=.=.=.=.            ",
"                                                                                                    =.=.=.=.=.=.=.              ",
"                                                                                                  =.=.=.=.=.=.=.                ",
"                                                                                                =.=.=.=.=.=.=.                  ",
"                                                                                              =.=.=.=.=.=.=.                    ",
"                                                                                            =.=.=.=.=.=.=.                      ",
"                                                                                          =.=.=.=.=.=.=.                        ",
"                                                                                        =.=.=.=.=.=.=.                          ",
"                                                                                      =.=.=.=.=.=.=.                            ",
"                                                                                    =.=.=.=.=.=.=.                              ",
"                                                                                  =.=.=.=.=.=.=.                                ",
"                                                                                =.=.=.=.=.=.=.                                  ",
"                                                                              =.=.=.=.=.=.=.                                    ",
"                                                                            =.=.=.=.=.=.=.                                      ",
"                                                                          =.=.=.=.=.=.=.                                        ",
"                                                                        =.=.=.=.=.=.=.                                          ",
"                                                                      =.=.=.=.=.=.=.                                            ",
"                                                                  =.=.=.=.=.=.=.=.                                              ",
"                                                              =.=.=.=.=.=.=.=.=.                                                ",
"                                                              =.=.=.=.=.=.=.=.                                                  ",
"                                                        B B B   =.=.=.=.=.=.                                                    ",
"                                                    B B B B B B B =.=.=.=.                                                      ",
"                                                  B B B B B B B B   =.=.                                                        ",
"                                              B B B B B B B B B B B B                                                           ",
"                                              B B B B B B B B B B B                                                             ",
"                                        B B B B B B B B B B B B B B                                                             ",
"                                    B B B B B B B B B B B B B B B                                                               ",
"                                      B B B B B B B B B B B B B B                                                               ",
"                                          B B B B B B B B B B B                                                                 ",
"                                              B B B B B B B                                                                     ",
"                                                          X                                                                     ",
"                        X * - w w = & . O O O # o   X X X X X X X           X X X X               @ = - - * @                   ",
"                    X w ) X.&.&.&.#...J b c c l 4 * ) ` ` ` ` ` ^ s &     + E ` ` ! &         - Q ..#.&.&.#. .R =               ",
"                  & ! &.=.=.=.=.=.=.%.U V V V b # - &.=.=.=.=.=.=.*. .e   @  .=.=.@.*     + R @.=.=.=.=.=.=.=.=.X.s X           ",
"                * } =.=.=.=.=.=.=.*.' V V V S ,   - &.=.=.=.=.=.=.=.=.X.q @  .=.=.@.*   @ ! &.=.=.=.=.=.=.=.=.=.=.&.E X         ",
"              + ) =.=.=.=.#.} ) ) [ A V V K +.H   - &.=.=.&.#.#.=.=.=.=.) &  .=.=.@.* X E *.=.=.=.&...) ` ..&.=.=.=.#.e         ",
"              d &.=.=.*.) 0 @ . f Z V V D o.=.@.- - &.=.=.` = - R &.=.=.#.0  .=.=.@.* w #.=.=.=. .e @   X & i ..=.&.Q &         ",
"            &  .=.=.=.^ @     3 N V V V ] *.=.=.Q - &.=.=.) X   @  .=.=.*.u  .=.=.@.= ) =.=.=.} *             - ) s X           ",
"            e &.=.=...*     % v V V V n a &.=.=...0 &.=.=.) X   + ` =.=.=.i  .=.=.@.0 @.=.=.@.0                 +               ",
"            E =.=.=.E     O j V V V V 4 @  .=.=.&.w &.=.=.) + + e #.=.=.&.0  .=.=.@.s =.=.=.) X                                 ",
"            ^ =.=.*.e   . g V V V V h .   ^ =.=.*.i &.=.=.X.} } #.=.=.=. .*  .=.=.@.R *.=.=.T                                   ",
"            ^ =.=.*.q   3 m V V V l #     ! =.=.*.s &.=.=.=.=.=.=.=.=.#.i @  .=.=.@.E =.=.*.T                                   ",
"            ! =.=.=.d $ v V V V n ;     X ) =.=.&.u &.=.=.@.=.=.=.=.#.T X @  .=.=.@.T &.=.=.Q                                   ",
"            s =.=.=.) z V V V V 4       = @.=.=.#.q &.=.=.` X.=.=.=.} +   @  .=.=.@.w &.=.=. .&                                 ",
"            = @.=.=.o.D V V V h .     + Q =.=.=.} - &.=.=.) d *.=.=.&.i   @  .=.=.@.- ..=.=.&.T X             X u =             ",
"            X ^ =.%.P V V V l #     @ R &.=.=.*.i - &.=.=.) & } =.=.=. .& @  .=.=.@.* R *.=.=.#.s +         @ R &. .e X         ",
"              0 O.' V V V I y - - s } *.=.=.=.` + - &.=.=.) X u &.=.=.*.R @  .=.=.@.* &  .=.=.=.&.` i 0 q d } &.=.=.#.i         ",
"              O x Z V V L $.&.#.#.=.=.=.=.=...-   - &.=.=.) X X ) =.=.=.X.-  .=.=.@.*   w X.=.=.=.=.*.&.&.*.=.=.=.=...-         ",
"            . g V V V F o.=.=.=.=.=.=.=.=. .0     - &.=.=.) X   0 @.=.=.=.!  .=.=.@.*     w ..=.=.=.=.=.=.=.=.=.&. .0           ",
"            4 N V V V Y #.*.=.=.=.=.&.@.Q *       - #.*.&.) X   X E &.*.=.@...=.&.X.*       = Q @.*.=.=.=.=.&.X.E &             ",
"          % v V V V V 7 t W { | | ( H 9 > ; ; ; : 1 p p a r ; ; ; 2 p a p p y a a y 1 ; ; ; ; > 9 H / { _ ~ G 8 : ; ; ; ; .     ",
"        O k V V V V V V V V C Z Z V V V V V V V V V V V V V V V V V V V V V V N V V V V V V V V V N V Z C V V V V V V V M $     ",
"      . g V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V M $     ",
"      3 M V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V V N V V V M $     ",
"      < 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 6 f 5 o     ",
"                                                                                                                                ",
"                                                                                                                                "
};
#if defined ALLEGRO_WITH_XWINDOWS && defined ALLEGRO_USE_CONSTRUCTOR
extern void *allegro_icon;
CONSTRUCTOR_FUNCTION(static void _set_allegro_icon(void));
static void _set_allegro_icon(void)
{
    allegro_icon = allegico_xpm;
}
#endif
