#include "communism.h"

extern void clrscr(void);
extern int printf(const char* format, ...);
extern char keyboard_getchar(void);
//Lets set the background to REEDDD!!
static void set_red_background(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x4F << 8) | c;
    }
}

static void restore_screen(void) {
    volatile unsigned short* vga_buffer = (volatile unsigned short*)0xB8000;
    for (int i = 0; i < 80 * 25; i++) {
        unsigned char c = vga_buffer[i] & 0xFF;
        vga_buffer[i] = (0x07 << 8) | c;
    }
}

static const char* manifesto_pages[] = {
    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Manifesto of the Communist Party\n\n"
    "A spectre is haunting Europe - the spectre of communism. All the powers of old Europe have\n"
    "entered into a holy alliance to exorcise this spectre: Pope and Tsar, Metternich and Guizot,\n"
    "French Radicals and German police-spies.\n\n"
    "Where is the party in opposition that has not been decried as communistic by its opponents in\n"
    "power? Where is the opposition that has not hurled back the branding reproach of communism,\n"
    "against the more advanced opposition parties, as well as against its reactionary adversaries?\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Two things result from this fact:\n"
    "I. Communism is already acknowledged by all European powers to be itself a power.\n"
    "II. It is high time that Communists should openly, in the face of the whole world,\n"
    "publish their views, their aims, their tendencies, and meet this nursery tale of the\n"
    "Spectre of Communism with a manifesto of the party itself.\n\n"
    "To this end, Communists of various nationalities have assembled in London and sketched the\n"
    "following manifesto, to be published in the English, French, German, Italian, Flemish and Danish\n"
    "languages.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "I. Bourgeois and Proletarians\n\n"
    "The history of all hitherto existing society is the history of class struggles.\n"
    "Freeman and slave, patrician and plebeian, lord and serf, guild-master and journeyman, in a\n"
    "word, oppressor and oppressed, stood in constant opposition to one another, carried on an\n"
    "uninterrupted, now hidden, now open fight, a fight that each time ended, either in a revolutionary\n"
    "reconstitution of society at large, or in the common ruin of the contending classes.\n\n"
    "In the earlier epochs of history, we find almost everywhere a complicated arrangement of society\n"
    "into various orders, a manifold gradation of social rank...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The modern bourgeois society that has sprouted from the ruins of feudal society has not done\n"
    "away with class antagonisms. It has but established new classes, new conditions of oppression,\n"
    "new forms of struggle in place of the old ones.\n\n"
    "Our epoch, the epoch of the bourgeoisie, possesses, however, this distinct feature: it has\n"
    "simplified class antagonisms. Society as a whole is more and more splitting up into two great\n"
    "hostile camps, into two great classes directly facing each other - Bourgeoisie and Proletariat.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "From the serfs of the Middle Ages sprang the chartered burghers of the earliest towns. From these\n"
    "burgesses the first elements of the bourgeoisie were developed.\n\n"
    "The discovery of America, the rounding of the Cape, opened up fresh ground for the rising\n"
    "bourgeoisie. The East-Indian and Chinese markets, the colonisation of America, trade with the\n"
    "colonies, the increase in the means of exchange and in commodities generally, gave to commerce,\n"
    "to navigation, to industry, an impulse never before known...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The feudal system of industry, in which industrial production was monopolised by closed guilds,\n"
    "now no longer sufficed for the growing wants of the new markets. The manufacturing system\n"
    "took its place. The guild-masters were pushed on one side by the manufacturing middle class;\n"
    "division of labour between the different corporate guilds vanished in the face of division of labour\n"
    "in each single workshop.\n\n"
    "Meantime the markets kept ever growing, the demand ever rising. Even manufacturer no longer\n"
    "sufficed. Thereupon, steam and machinery revolutionised industrial production...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Modern industry has established the world market, for which the discovery of America paved the\n"
    "way. This market has given an immense development to commerce, to navigation, to\n"
    "communication by land. This development has, in its turn, reacted on the extension of industry;\n"
    "and in proportion as industry, commerce, navigation, railways extended, in the same proportion\n"
    "the bourgeoisie developed, increased its capital, and pushed into the background every class\n"
    "handed down from the Middle Ages.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The bourgeoisie, historically, has played a most revolutionary part.\n\n"
    "The bourgeoisie, wherever it has got the upper hand, has put an end to all feudal, patriarchal,\n"
    "idyllic relations. It has pitilessly torn asunder the motley feudal ties that bound man to his\n"
    "\"natural superiors\", and has left remaining no other nexus between man and man than naked self-\n"
    "interest, than callous \"cash payment\". It has drowned the most heavenly ecstasies of religious\n"
    "fervour, of chivalrous enthusiasm, of philistine sentimentalism, in the icy water of egotistical\n"
    "calculation...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The bourgeoisie has stripped of its halo every occupation hitherto honoured and looked up to with\n"
    "reverent awe. It has converted the physician, the lawyer, the priest, the poet, the man of science,\n"
    "into its paid wage labourers.\n\n"
    "The bourgeoisie has torn away from the family its sentimental veil, and has reduced the family\n"
    "relation to a mere money relation.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The bourgeoisie cannot exist without constantly revolutionising the instruments of production,\n"
    "and thereby the relations of production, and with them the whole relations of society.\n\n"
    "All fixed, fast-frozen relations, with their train of ancient and venerable prejudices and opinions,\n"
    "are swept away, all new-formed ones become antiquated before they can ossify. All that is solid\n"
    "melts into air, all that is holy is profaned, and man is at last compelled to face with sober\n"
    "senses his real conditions of life, and his relations with his kind.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The need of a constantly expanding market for its products chases the bourgeoisie over the entire\n"
    "surface of the globe. It must nestle everywhere, settle everywhere, establish connexions\n"
    "everywhere.\n\n"
    "The bourgeoisie has through its exploitation of the world market given a cosmopolitan character\n"
    "to production and consumption in every country... In place of the old local and national seclusion\n"
    "and self-sufficiency, we have intercourse in every direction, universal inter-dependence of nations.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The bourgeoisie has subjected the rule of the towns over the country. It has created enormous\n"
    "cities, has greatly increased the urban population as compared with the rural, and has thus rescued\n"
    "a considerable part of the population from the idiocy of rural life...\n\n"
    "The bourgeoisie, during its rule of scarce one hundred years, has created more massive and more\n"
    "colossal productive forces than have all preceding generations together.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "A similar movement is going on before our own eyes. Modern bourgeois society, with its\n"
    "relations of production, of exchange and of property, a society that has conjured up such gigantic\n"
    "means of production and of exchange, is like the sorcerer who is no longer able to control the\n"
    "powers of the nether world whom he has called up by his spells...\n\n"
    "The weapons with which the bourgeoisie felled feudalism to the ground are now turned against\n"
    "the bourgeoisie itself.\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "But not only has the bourgeoisie forged the weapons that bring death to itself; it has also called\n"
    "into existence the men who are to wield those weapons - the modern working class - the\n"
    "proletarians.\n\n"
    "In proportion as the bourgeoisie, i.e., capital, is developed, in the same proportion is the\n"
    "proletariat, the modern working class, developed - a class of labourers, who live only so long as\n"
    "they find work, and who find work only so long as their labour increases capital...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Modern Industry has converted the little workshop of the patriarchal master into the great factory\n"
    "of the industrial capitalist. Masses of labourers, crowded into the factory, are organised like\n"
    "soldiers. As privates of the industrial army they are placed under the command of a perfect\n"
    "hierarchy of officers and sergeants...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The proletariat goes through various stages of development. With its birth begins its struggle with\n"
    "the bourgeoisie. At first the contest is carried on by individual labourers, then by the workpeople\n"
    "of a factory, then by the operative of one trade, in one locality, against the individual bourgeois\n"
    "who directly exploits them...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "But with the development of industry, the proletariat not only increases in number; it becomes\n"
    "concentrated in greater masses, its strength grows, and it feels that strength more. The various\n"
    "interests and conditions of life within the ranks of the proletariat are more and more equalised...\n\n"
    "This organisation of the proletarians into a class, and, consequently into a political party, is\n"
    "continually being upset again by the competition between the workers themselves...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Of all the classes that stand face to face with the bourgeoisie today, the proletariat alone is a\n"
    "really revolutionary class. The other classes decay and finally disappear in the face of Modern\n"
    "Industry; the proletariat is its special and essential product.\n\n"
    "The lower middle class, the small manufacturer, the shopkeeper, the artisan, the peasant, all these\n"
    "fight against the bourgeoisie, to save from extinction their existence as fractions of the middle class...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "The proletarians cannot become masters of the productive forces of society, except by abolishing\n"
    "their own previous mode of appropriation, and thereby also every other previous mode of appropriation.\n\n"
    "All previous historical movements were movements of minorities, or in the interest of minorities.\n"
    "The proletarian movement is the self-conscious, independent movement of the immense majority,\n"
    "in the interest of the immense majority...\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell",

    "=== THE COMMUNIST MANIFESTO ===\n\n"
    "Conclusion / Grave-diggers\n\n"
    "What the bourgeoisie therefore produces, above all, are its own grave-diggers. Its fall\n"
    "and the victory of the proletariat are equally inevitable.\n\n"
    "WORKING MEN OF ALL COUNTRIES, UNITE!!!!!!!!\n\n"
    "[A] Previous page | [D] Next page | [Q] Return to shell"
};
//fuck that was a lot
#define TOTAL_PAGES 20

void cmd_communism(void) {
    int current_page = 0;
    while (1) {
        clrscr(); 
        printf("%s\n", manifesto_pages[current_page]);
        set_red_background();

        char key = keyboard_getchar();
        //Dean withers + communism + socialism = politically educated o algo
        if (key == 'a' || key == 'A') {
            if (current_page > 0) {
                current_page--;
            }
        }
        else if (key == 'd' || key == 'D') {
            if (current_page < TOTAL_PAGES - 1) {
                current_page++;
            }
        }
        else if (key == 'q' || key == 'Q') {
            break; 
        }
    }

    restore_screen();
    clrscr();
    printf("\nReturned to shell.\n");
}