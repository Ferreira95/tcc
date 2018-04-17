$(document).ready(function()
{
	$("#aumentar-fonte").click(function () {
		let size = $(".card-text").css('font-size');

		size = size.replace('px', '');
		size = parseInt(size) + 2;

		$(".font").animate({'font-size' : size + 'px'});
		return false;
	});

	$("#diminuir-fonte").click(function ()
	{
		let size = $(".card-text").css('font-size');

		size = size.replace('px', '');
		size = parseInt(size) - 2;

		$(".font").animate({'font-size' : size + 'px'});
		return false;
	});
});
