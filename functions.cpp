#include "functions.h"
//#include <iostream>


bool alcoholic_cocktails[12]={true, true, true, true, true, true, true, false, false, false, false, false};
bool non_alcoholic_cocktails[18]= {true, true, true, true, true, true, true, true, true, true, true, false,false,false,false,false,false,false}; 

/* Alkoholische Cocktails*/
void wodka_maracuja_1(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2 == true)
  {
    alcoholic_cocktails[0]= true;
  }
  else
  {

     alcoholic_cocktails[0]= false;
  }




}
void malibu_maracuja_2(bool &ingredient, bool &ingredient2)
{

  if (ingredient == true && ingredient2 == true)
  {
     alcoholic_cocktails[1]= true;
   
  }
  else
  {

     alcoholic_cocktails[1]= false;
  }


}

void malibu_orange_3(bool &ingredient, bool &ingredient2)
{


  if (ingredient == true && ingredient2 == true)
  {
    alcoholic_cocktails[2]= true;
    
  }
  else
  {
    alcoholic_cocktails[2]= false;
    
  }

}

void malibu_orange_grenadine_4(bool &ingredient, bool &ingredient2, bool &ingredient3)
{

  if (ingredient == true && ingredient2 == true && ingredient3==true)
  {

    alcoholic_cocktails[3]= true;
  }
  else
  {
    alcoholic_cocktails[3]= false;
    
  }

}

void wodka_orange_5(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2 == true)
  {
    alcoholic_cocktails[4]= true;
    
  }
  else
  {

    alcoholic_cocktails[4]= false;
  }

}

void wodka_malibu_orange_6(bool &ingredient, bool &ingredient2, bool &ingredient3)
{

  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {

    alcoholic_cocktails[5]= true;
  }
  else
  {
    alcoholic_cocktails[5]= false;
    
  }
}

void wodka_malibu_ananas_7(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {

     alcoholic_cocktails[6]= true;
  }
  else
  {
    alcoholic_cocktails[6]= false;
   
  }


}

void wodka_grenadine_ananas_8(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {
    alcoholic_cocktails[7]= true;
    
  }
  else
  {
    alcoholic_cocktails[7]= false;
    
  }
}


void wodka_zitrone_9(bool &ingredient, bool &ingredient2)
{

  if (ingredient == true && ingredient2 == true)
  {
    alcoholic_cocktails[8]= true;
    
  }
  else
  {
    alcoholic_cocktails[8]= false;
   
  }
}

void wodka_zitrone_maracuja_ananas_grenadine_banane_orange_10(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4, bool &ingredient5, bool &ingredient6, bool &ingredient7)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true &&ingredient4==true &&ingredient5==true&&ingredient6==true&&ingredient7==true)
  {

    alcoholic_cocktails[9]= true;
  }
  else
  {
    alcoholic_cocktails[9]= false;
  }



}

void wodka_ananas_11(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2 == true)
  {
     alcoholic_cocktails[10]= true;
  
  }
  else
  {

    alcoholic_cocktails[10]= false;
  }

}

void wodka_orange_12(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2 == true)
  {
    alcoholic_cocktails[11]= true;
    
  }
  else
  {

    alcoholic_cocktails[11]= false;
  }
}




/* Antialkoholische Cocktails*/

void maracuja_1(bool &ingredient)
{
  if (ingredient == true)
  {
   non_alcoholic_cocktails[0]= true;

  }
  else
  {
   non_alcoholic_cocktails[0]= false;
  }

}
void orange_2(bool &ingredient)
{
  if (ingredient == true)
  {
    non_alcoholic_cocktails[1]= true;


  }
  else
  {
    non_alcoholic_cocktails[1]= false;
  }



}
void maracuja_orange_ananas_zitrone_grenadine_3(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4, bool &ingredient5)
{

  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4==true && ingredient5==true)
  {
      non_alcoholic_cocktails[2]= true;
    
  }
  else
  {
      non_alcoholic_cocktails[2]= false;
    
  }

}
void banane_ananas_maracuja_grenadine_4(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true)
  {

    non_alcoholic_cocktails[3]= true;
  }
  else
  {
   non_alcoholic_cocktails[3]= false;
   
  }


}
void zitrone_orange_5(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2==true)
  {
     non_alcoholic_cocktails[4]= true;

  }
  else
  {
    non_alcoholic_cocktails[4]= false;
  }
}
void grenadine_zitrone_orange_maracuja_ananas_6(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4, bool &ingredient5)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true && ingredient5==true)
  {
    non_alcoholic_cocktails[5]= true;
   
  }
  else
  {

    non_alcoholic_cocktails[5]= false;
  }
}
void zitrone_grenadine_orangensaft_ananas_7(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true)
  {
    non_alcoholic_cocktails[6]= true;
  }
  else
  {
   non_alcoholic_cocktails[6]= false;
   
  }
}
void zitrone_grenadine_orange_maracuja_ananas_8(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4, bool &ingredient5)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true && ingredient5 == true)
  {
       non_alcoholic_cocktails[7]= true;
    
  }
  else
  {

    non_alcoholic_cocktails[7]= false;
  }
}
void zitrone_grenadine_maracuja_orange_ananas_9(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4, bool &ingredient5)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true && ingredient5 == true)
  {

   
    non_alcoholic_cocktails[8]= true;
  }
  else
  {

    
    non_alcoholic_cocktails[8]= false;
  }
}
void grenadine_zitrone_orange_banane_10(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true)
  {
      non_alcoholic_cocktails[9]= true;
   
  }
  else
  {

      non_alcoholic_cocktails[9]= false;
  }
}
void zitrone_grenadine_maracuja_ananas_11(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true)
  {

    non_alcoholic_cocktails[10]= true;
  }
  else
  {
    non_alcoholic_cocktails[10]= false;
    
  }
}
void zitrone_grenadine_orange_maracuja_12(bool &ingredient, bool &ingredient2, bool &ingredient3, bool &ingredient4)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true && ingredient4 == true)
  {
      non_alcoholic_cocktails[11]= true;
  
  }
  else
  {

     non_alcoholic_cocktails[11]= false;
  
  }
}
void ananas_orange_13(bool &ingredient, bool &ingredient2)
{
  if (ingredient == true && ingredient2 == true)
  {
    non_alcoholic_cocktails[12]= true;

  }
  else
  {
    non_alcoholic_cocktails[12]= false;
  }
}
void zitrone_orange_ananas_14(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true &&ingredient3==true)
  {
    non_alcoholic_cocktails[13]= true;

  }
  else
  {
    non_alcoholic_cocktails[13]= false;
  }
}
void zitrone_orange_ananas_15(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {
    non_alcoholic_cocktails[14]= true;
  }
  else
  {
    non_alcoholic_cocktails[14]= false;
  }
}
void grenadine_orange_ananas_16(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {
    non_alcoholic_cocktails[15]= true;

  }
  else
  {
    non_alcoholic_cocktails[15]= false;
  }
}
void orange_maracuja_ananas_17(bool &ingredient, bool &ingredient2, bool &ingredient3)
{

  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {
    
    non_alcoholic_cocktails[16]= true;
  }
  else
  {
   non_alcoholic_cocktails[16]= false;
  }
}
void grenadine_orange_ananas_18(bool &ingredient, bool &ingredient2, bool &ingredient3)
{
  if (ingredient == true && ingredient2 == true && ingredient3 == true)
  {
    
    non_alcoholic_cocktails[17]= true;

  }
  else
  {
    non_alcoholic_cocktails[17]= false;
  }

}
