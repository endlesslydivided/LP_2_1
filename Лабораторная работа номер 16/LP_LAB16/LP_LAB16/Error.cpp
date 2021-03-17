#include "Error.h"
namespace Error
{
	// серии ошибок: 0-99 - системные ошибки
//				 100-109 - ошибки параметров
//				 110-119 - ошибки открытия и чтения файлов
//				 120-129 - лексические ошибки
	ERROR error[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,	"Недопустимый код ошибки"),
		ERROR_ENTRY(1,	"Системный сбой"),
		ERROR_ENTRY_NODEF(2),ERROR_ENTRY_NODEF(3),ERROR_ENTRY_NODEF(4),ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6),ERROR_ENTRY_NODEF(7),ERROR_ENTRY_NODEF(8),ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10),ERROR_ENTRY_NODEF10(20),ERROR_ENTRY_NODEF10(30),ERROR_ENTRY_NODEF10(40),ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60),ERROR_ENTRY_NODEF10(70),ERROR_ENTRY_NODEF10(80),ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100,	"Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101),ERROR_ENTRY_NODEF(102),ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104,	"Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105),ERROR_ENTRY_NODEF(106),ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108),ERROR_ENTRY_NODEF(109),

		ERROR_ENTRY(110,	"Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111,	"Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112,	"Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113,	"Ошибка при создании файла выхода (-out)"),
		ERROR_ENTRY_NODEF(114),
		ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116),
		ERROR_ENTRY_NODEF(117),
		ERROR_ENTRY_NODEF(118),
		ERROR_ENTRY_NODEF(119),

		ERROR_ENTRY(120,	"Таблица лексем переполнена"),
		ERROR_ENTRY(121,	"Слишком большое имя переменной или недопустимое имя переменной"),
		ERROR_ENTRY(122,	"Таблица идентификаторов переполнена."),
		ERROR_ENTRY(123,	"Нераспознанная лексема"),
		ERROR_ENTRY(124,	"Нарушен формат строкового литерала"),
		ERROR_ENTRY(125,	"Перезапись идентификатора"),
		ERROR_ENTRY(126,	"Неизвестная переменная"),
		ERROR_ENTRY(127,	"Превышена длина строкового литерала"),
		ERROR_ENTRY(128,	"Не удалось создать файл с лексемами или идентификаторами"),
		ERROR_ENTRY(129,	"Повторное объявление main"),

		ERROR_ENTRY(130,	"Отсутствие ключевого слова declare при объявлении переменной"),
		ERROR_ENTRY_NODEF(131),ERROR_ENTRY_NODEF(132),ERROR_ENTRY_NODEF(133),ERROR_ENTRY_NODEF(134),ERROR_ENTRY_NODEF(135),
		ERROR_ENTRY_NODEF(136),ERROR_ENTRY_NODEF(137),ERROR_ENTRY_NODEF(138),ERROR_ENTRY_NODEF(139),
		ERROR_ENTRY_NODEF10(140),ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160),ERROR_ENTRY_NODEF10(170),
		ERROR_ENTRY_NODEF10(180),ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200),
		ERROR_ENTRY_NODEF100(300),
		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600,"Неверная структура программы"),
		ERROR_ENTRY(601,"Ошибочный оператор"),
		ERROR_ENTRY(602,"Ошибка в выражении"),
		ERROR_ENTRY(603,"Ошибка в параметрах функции"),
		ERROR_ENTRY(604,"Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY_NODEF(605),
		ERROR_ENTRY_NODEF(606),
		ERROR_ENTRY_NODEF(607),
		ERROR_ENTRY_NODEF(608),
		ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610),ERROR_ENTRY_NODEF10(620),ERROR_ENTRY_NODEF10(630),ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),ERROR_ENTRY_NODEF10(660),ERROR_ENTRY_NODEF10(670),ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),

		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800),
		ERROR_ENTRY_NODEF100(900)
	};
	ERROR geterror( int _id)
	{
		ERROR er;
		if (_id < 0 || _id > ERROR_MAX_ENTRY)
			er = error[0];
		else
			er = *(error + _id);
		return er;
	}
	ERROR geterrorin( int _id, int line = -1, int col = -1)
	{
		ERROR er;

		if (_id < 0 || _id > ERROR_MAX_ENTRY)
			er = error[0];
		else
		{
			er = error[_id];
			er.inext.line = line;
			er.inext.col = col;
		}
		return er;
	}
};