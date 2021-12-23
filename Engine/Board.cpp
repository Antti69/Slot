#include "Board.h"

Board::Board(const Vei2 topleft)
	:
	topleft(topleft)
{
	winclass = { { 7, 4 }, {6, 8}, {5, 12}, {4, 20}, {3, 25}, {2, 50}, {1, 100}, {0, 200} };
}

void Board::Draw(Graphics& gfx) const
{
	std::string money1 = std::to_string(money);
	std::string numrolls = std::to_string(NumberOfrolls);
	std::string Numwins = std::to_string(NumberOfWins);
	std::string bets = std::to_string(bet);
	std::string r0 = std::to_string(range01);
	std::string r1 = std::to_string(range23);
	std::string r2 = std::to_string(range45);
	std::string r3 = std::to_string(range67);

	DrawBorders(gfx);

	font.DrawTexts(bets, Vei2(topleft.x + spacewidth, topleft.y - borderheight), gfx, Colors::Green);
	font.DrawTexts("BET", Vei2(topleft.x, topleft.y - borderheight), gfx, Colors::Green);

	font.DrawTexts(money1, Vei2(topleft.x + width + borderwidth + spacewidth, topleft.y), gfx, Colors::Green);
	font.DrawTexts("Money", Vei2(topleft.x + width + borderwidth, topleft.y), gfx, Colors::Green);

	font.DrawTexts(numrolls, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + borderheight), gfx, Colors::Green);
	font.DrawTexts("Number Of Rolls", Vei2(topleft.x + width + borderwidth, topleft.y + borderheight), gfx, Colors::Green);

	font.DrawTexts(Numwins, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + borderheight + borderheight), gfx, Colors::Green);
	font.DrawTexts("Number Of Wins", Vei2(topleft.x + width + borderwidth, topleft.y + borderheight + borderheight), gfx, Colors::Green);

	font.DrawTexts(r0, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 3)),
		gfx, Colors::Green);
	font.DrawTexts(r1, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 4)),
		gfx, Colors::Green);
	font.DrawTexts(r2, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 5)),
		gfx, Colors::Green);
	font.DrawTexts(r3, Vei2(topleft.x + width + borderwidth + (spacewidth * 3), topleft.y + (borderheight * 6)),
		gfx, Colors::Green);
	line0.Draw(gfx);
	line1.Draw(gfx);
	line2.Draw(gfx);
}

void Board::Update()
{
	int counter = 10;
	int lastcounter = 1;
	line0.Procces(counter, 0, 8);
	line1.Procces(counter, 0, 8);
	if (line0.GetFruit() == line1.GetFruit())
	{
		//lastcounter = 3;
	}
	line2.Procces(lastcounter, 0, 8);
	NumberOfrolls++;
	if (CheckWin())
	{
		//money += 32;
		money += CalculateWin();
		NumberOfWins++;
		if (line0.GetFruit() < 2)
		{
			range01++;
		}
		else if (line0.GetFruit() >= 2 && line0.GetFruit() < 4)
		{
			range23++;
		}
		else if (line0.GetFruit() >= 4 && line0.GetFruit() < 6)
		{
			range45++;
		}
		else
		{
			range67++;
		}
	}
}

void Board::DrawBorders(Graphics& gfx) const
{
	gfx.DrawRectLines(topleft.x, topleft.y, topleft.x + width, topleft.y + height, Colors::Blue);
}

bool Board::CheckWin() const
{
	std::vector<int> win;
	int i = line0.GetFruit();
	win.push_back(line1.GetFruit());
	win.push_back(line2.GetFruit());
	return std::all_of(win.begin(), win.end(), [&i](int l) {return l == i; });
}

int Board::CalculateWin() const
{
	return winclass.find(line0.GetFruit())->second;
}

void Board::CalculateFruitPos(Fruits& line)
{
	line.currentXfruit = line.Fruit % line.width;
	line.currentYfruit = line.Fruit / line.width;
	line.rectpos = { line.currentXfruit * line.dim, line.currentYfruit * line.dim };
	line.picslice = RectI(line.rectpos, line.dim, line.dim);
}
