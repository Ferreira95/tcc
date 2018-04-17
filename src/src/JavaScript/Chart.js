	function chartProject(ni, ep, c, ctx) 
	{
		var myChart = new Chart(ctx,
		{
   			type: 'pie',
			data:
			{
				datasets: 
				[{
            				label:"Status dos dados",				
            				data: [ni, ep, c],
					backgroundColor: 
					[
                				'rgba(255, 99, 132, 0.2)',
                				'rgba(54, 162, 235, 0.2)',
                				'rgba(255, 206, 86, 0.2)',
                		        ],
		            		borderColor: 
					[
				                'rgba(255,99,132,1)',
				                'rgba(54, 162, 235, 1)',
				                'rgba(255, 206, 86, 1)',
				        ],
            				borderWidth: 1
        			}],
				labels: ['Não iniciado', 'Em processo', 'Concluído'],
				options:
				{
					legend:
					{
						position: 'bottom'
					}
				}
			}
		}); 
     }

	function chartProjectMin(ni, c, ctx) 
	{
		var myChart = new Chart(ctx,
		{
   			type: 'pie',
			data:
			{
				datasets: 
				[{
            				label:"Status dos dados",				
            				data: [ni, c],
					backgroundColor: 
					[
                				'rgba(255, 99, 132, 0.2)',
                				'rgba(54, 162, 235, 0.2)',
                		        ],
		            		borderColor: 
					[
				                'rgba(255,99,132,1)',
				                'rgba(54, 162, 235, 1)',
				        ],
            				borderWidth: 1
        			}],
				labels: ['Dados na fila %', 'Resultados adquiridos %'],
				options:
				{
					legend:
					{
						position: 'bottom'
					}
				}
			}
		}); 
     }

