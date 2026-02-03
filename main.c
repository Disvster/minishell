#include "incs/minishell.h"

int	main(void)
{
	int	*j = malloc(4);
	int	i;
	t_list	*test;
	t_list	*new;

	i = 0;
	test = NULL;
	new = NULL;
	while (i < 3)
	{
		new = ft_lstnew(&i);
		if (!test)
			test = new;
		else
			ft_lstadd_back(&test, new);
		i++;
	}
	t_list *temp = test;
	i = 0;
	while (temp)
	{
		j = (int *)temp->content;
		printf("%i\n", *j);
		temp = temp->next;
	}
}
