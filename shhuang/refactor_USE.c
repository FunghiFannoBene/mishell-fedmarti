#include "../minishell.h"
#include "../pipeline.h"
#include "short_code.h"

void	init_transform_d(t_short_dollar *d)
{
	d->tmp = NULL;
	d->i = -1;
	d->env_len = 0;
	d->save = 0;
	d->save_pre = 0;
	d->size = 0;
	d->slash_count = 0;
	d->start = 0;
	d->flag = 0;
}

int	create_flags(char *s, t_short_dollar *d)
{
	d->tmp = NULL;
	if (s[d->i] == '\\')
	{
		while (s[d->i] == '\\')
		{
			d->slash_count++;
			d->i++;
		}
	}
	else
		d->slash_count = 0;
	if (s[d->i] == '\'')
		d->flag = 1;
	while (s[d->i] && d->flag == 1)
	{
		d->i++;
		if (s[d->i] == '\'')
			d->flag = 0;
	}
	d->start = d->i;
	return (1);
}

char	*transform_for_dollar(char *s, t_data *data)
{
	t_var			*list;
	t_short_dollar	d;

	init_transform_d(&d);
	while (s[++d.i] != '\0')
	{
		if (create_flags(s, &d) && s[d.i] == '\0')
			return (s);
		d.env_len = checksymbol(s + d.i + 1);
		if (s[d.i] == '$' && d.slash_count % 2 == 0 && d.env_len)
		{
			d.save = s[d.i + d.env_len];
			s[d.i + d.env_len] = '\0';
			list = search_variable_tvar(s + d.i, data);
			s[d.i + d.env_len] = d.save;
			if (list != NULL)
			{
				d.tmp = add_slashes(ft_strdup(list->value));
				d.size = ft_strlen(d.tmp);
				d.i += d.size + 1;
			}
			s = replace_for_new_str(s, d.tmp, d.start, d.size);
		}
	}
	return (s);
}
