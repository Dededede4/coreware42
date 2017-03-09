/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init_champ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gnebie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 04:16:24 by gnebie            #+#    #+#             */
/*   Updated: 2017/03/08 16:45:35 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"
#include "../../includes/global.h"

static int		vm_size_champ(t_champ *champ, t_datas *datas)
{
	int size;
	int save;

	size = 0;
	while ((int)champ->champ[size] > 0 && (int)champ->champ[size] < 17)
	{
		save = size;
		if (vm_have_ocp((int)champ->champ[size]))
		{

			size += vm_ocp_size(champ->champ[size + 1], 3,
					op_tab[(int)champ->champ[size]].nbr_octet_dir);
			size += 2;
		}
		else
		{
			size += vm_havent_ocp((int)champ->champ[size]);
			size ++;
		}
		if (datas->flag & FLAG_V)
			ft_printf("Size Op%i [%x] : %i\n", (int)champ->champ[save],
				champ->champ[save + 1], size);
	}
	return (size);
}

static void		vm_verif_champ(char *chmp_info, t_champ *champ)
{
	int		i;
	unsigned char *c;

	c = (unsigned char*)chmp_info;
	i = COREWAR_EXEC_MAGIC;
	if (c[0] == (i >> 24) && c[1] == ((i >> 16) & 0xff)
	&& c[2] == ((i >> 8) & 0xff) && c[3] == (i & 0xff))
		;
	else
		exit(ft_int_error("magic exec invalide"));
	ft_memcpy(champ->champ_name, chmp_info + 4, PROG_NAME_LENGTH);
}

static int			vm_create_champ(t_champ *champs, char *entry, int i,
									t_datas *datas)
{
	int		fd;
	char	buff[sizeof(header_t) + CHAMP_MAX_SIZE + 1];

	if (1 > (fd = open(entry, O_RDONLY)))
		exit (ft_int_error("Echec de lecture du champion"));
	if (read(fd, &buff, sizeof(header_t) + CHAMP_MAX_SIZE) == -1)
		exit (ft_int_error("Echec de read du champion"));
	buff[sizeof(header_t) + CHAMP_MAX_SIZE] = 0;
	vm_verif_champ(buff, &champs[i]);
	ft_memmove((void *)&champs[i], (void *)(buff + sizeof(header_t)),
				CHAMP_MAX_SIZE);
	champs[i].champ_nbr = i;
	champs[i].champ_size = vm_size_champ(&champs[i], datas);
	if (close(fd) == -1)
		exit (ft_int_error("Echec de close du champion"));
	return (0);
}

int				vm_init_champ(t_champ *champs, int argc, char **argv,
								t_datas *datas)
{
	int		champ_nbr;
	int		i;

	i = datas->player_nbr;
	champ_nbr = 0;
	while (i < argc)
	{
		vm_create_champ(champs, argv[i], champ_nbr, datas);
		if (datas->flag & FLAG_V)
			ft_printf("champ_size %d, champ nbr %d\n", champs[i - 1].champ_size,
					champs[i - 1].champ_nbr);
		++i;
		++champ_nbr;
	}
	return (champ_nbr);
}
