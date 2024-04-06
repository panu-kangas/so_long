#include "so_long_bonus.h"

void	start_message(void)
{
	ft_printf("\n\n");
	ft_printf("*******************************************\n");
	ft_printf("*      Hi there, welcome to so_long!      *\n");
	ft_printf("*                                         *\n");
	ft_printf("*  This game was created by Panu Kangas.  *\n");
	ft_printf("*     I really hope you enjoy it =)       *\n");
	ft_printf("*                                         *\n");
	ft_printf("*          Game instructions:             *\n");
	ft_printf("*                                         *\n");
	ft_printf("*    - Use WASD keys to move the king.    *\n");
	ft_printf("*    - Press H to use the hammer.         *\n");
	ft_printf("*    - Collect the diamonds.              *\n");
	ft_printf("*    - Watch out for the evil pigs!       *\n");
	ft_printf("*    - After last diamond, move to exit.  *\n");
	ft_printf("*      (use shortest route possible!)     *\n");
	ft_printf("*******************************************\n\n");
	ft_printf("First, please choose a difficulty level for the game.\n");
	ft_printf("(press e for easy, h for hard or g for god-mode\
	and then hit enter):\n");
}

void	end_message(void)
{
	ft_printf("\n");
	ft_printf("****************************************\n");
	ft_printf("*        Thank you for playing!        *\n");
	ft_printf("*           See you again! =)          *\n");
	ft_printf("****************************************\n\n");
}
