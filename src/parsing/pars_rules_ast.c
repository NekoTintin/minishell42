/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_rules_ast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchallat <bchallat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:04:27 by bchallat          #+#    #+#             */
/*   Updated: 2025/02/26 17:11:06 by bchallat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  this file have rules of abstraite sintix tree   */

/*list of rules

---		pipeline et commande	---

pipeline      → command { PIPE command }
command       → simple_command { redirection }
simple_command → WORD { WORD }


---		gestion des redirection		---

redirection  → REDIRECT_IN WORD  
             | REDIRECT_OUT WORD  
             | APPEND WORD  
             | HEREDOC WORD


--	-	gestion des varibles et citation	---

WORD         → WORD_PART { WORD_PART }
WORD_PART    → ALPHA | DIGIT | VAR_ENV | S_QUOTES | D_QUOTES






*/
