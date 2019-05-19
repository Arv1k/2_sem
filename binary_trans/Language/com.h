CMD_FORM(sin, 3, 65, {
						return CrtNode(MODE_SIGN, '*',
									   diff(position->Right),
									   CrtNode_op("cos",
												  copy(position->Right)));
					 })

CMD_FORM(cos, 3, 66, {
						return CrtNode(MODE_SIGN, '*',
									   CrtNode(MODE_NUMBER, -1,
									   		   nullptr,
									   		   nullptr),
									   CrtNode(MODE_SIGN, '*',
									   		   diff(position->Right),
									   		   CrtNode_op("sin",
												  		  copy(position->Right))));
					 })

CMD_FORM(tg, 2, 67, {

                    })

CMD_FORM(ctg, 3, 68, {})
CMD_FORM(ln, 2, 69, {
						return CrtNode(MODE_SIGN, '*',
									   diff(position->Right),
									   CrtNode(MODE_SIGN, '/',
									   		   CrtNode(MODE_NUMBER, 1,
									   		   		   nullptr,
									   		   		   nullptr),
									   		    copy(position->Right)));
					})

CMD_FORM(lg, 2, 70, {})
CMD_FORM(arcsin, 6, 71, {})
CMD_FORM(arccos, 6, 72, {})
CMD_FORM(arctg, 5, 73, {})
CMD_FORM(arcctg, 6, 74, {})
CMD_FORM(sh, 2, 75, {})
CMD_FORM(ch, 2, 76, {})
CMD_FORM(th, 2, 77, {})
CMD_FORM(cth, 3, 78, {})
CMD_FORM(sqrt, 4, 79, {})
CMD_FORM(exp, 3, 80, {
                        return CrtNode(MODE_SIGN, '*',
                                       diff(position->Right),
                                       copy(position));
                     })