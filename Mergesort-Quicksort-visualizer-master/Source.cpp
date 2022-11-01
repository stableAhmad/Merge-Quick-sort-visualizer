#include <iostream>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>



int width = 5;
sf::Time delayTime = sf::milliseconds(4);
int windowHeight =950;
int windowWidth = 1900;
int rectsSize = 267;
std::vector<sf::RectangleShape> rects;
sf::Font font;

sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Visualizer" , sf::Style::Titlebar | sf::Style::Close);

sf::Text createText(std::string s, int  x, int  y, int size);
void quickSort();
void showText();
void initializeRects();
void renderRects();
bool init();
void merge(std::vector<sf::RectangleShape> *array, int left, int mid, int right);
void mergeSort(std::vector < sf::RectangleShape> *array, int left, int right);

int main()
{
	init();
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{ 
		if (event.type == sf::Event::Closed)window.close();
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::A :
				quickSort();
				break;
			case sf::Keyboard::B :
				mergeSort(&rects, 0, rects.size() - 1);
					break;
			case sf::Keyboard:: R:
				initializeRects();
					break;
			
			}
		}
		}

		window.clear();
		renderRects();	
		showText();
		window.display();

	}

}


void quicksort(int s, int e)
{
	if (s == e)return;
	if (s > e)return;

	int p = e;
	int c = s;

	rects[p].setFillColor(sf::Color::Green);
	
	for (int i = s; i < e; i++)
	{
		rects[i].setFillColor(sf::Color::Cyan);
		window.clear();
		renderRects();
		window.display();
		sf::sleep(delayTime);
		rects[i].setFillColor(sf::Color::White);
		if (rects[i].getSize().y < rects[p].getSize().y)
		{
			sf::RectangleShape temp = rects[i];
			rects[i] = rects[c];
			rects[c] = temp;
			c++;
		}
	}

	sf::RectangleShape temp = rects[p];
	rects[p] = rects[c];
	rects[c] = temp;
	rects[c].setFillColor(sf::Color::White);
	quicksort(s, c - 1);

	quicksort(c+1 , p);

}

void quickSort()
{
	quicksort(0, rects.size() - 1);
}


void merge(std::vector<sf::RectangleShape> *array, int left, int mid, int right )
{
	int leftSize = mid - left + 1;
	int rightSize = right - mid;
	std::vector<sf::RectangleShape>* leftArr = new std::vector<sf::RectangleShape>();
	std::vector < sf::RectangleShape>* rightArr = new std::vector<sf::RectangleShape>();

	for (int i = 0; i < leftSize; i++)
	{
		leftArr->push_back((*array)[i+left]);
	}

	for (int i = 0; i < rightSize; i++)
	{
		rightArr->push_back((*array)[i+mid+1]);
	}
	int i = 0, j = 0;
	int m = left;
	while (i < leftSize && j < rightSize)
	{
		
		if (  (*leftArr)[i].getSize().y < (*rightArr)[j].getSize().y)
		{
			(*array)[m] = (*leftArr)[i];
			window.clear();
			renderRects();
			window.display();
			sf::sleep(delayTime);
			i++;
		}
		else
		{
			(*array)[m] = (*rightArr)[j];
			window.clear();
			renderRects();
			window.display();
			j++;
		}
		m++;
	}
	while (i < leftSize)
	{
		(*array)[m] = (*leftArr)[i];
		window.clear();
		renderRects();
		window.display();
		m++;
		i++;
	}

	while (j < rightSize)
	{
		(*array)[m] = (*rightArr)[j];
		window.clear();
		renderRects();
		window.display();
		j++;
		m++;
	}
	
}

void mergeSort(std::vector < sf::RectangleShape> *array, int left, int right)
{
	if (left >= right)return;
	int mid =left + (right - left) / 2;
	mergeSort(array, left, mid);
	mergeSort(array, mid + 1, right);
	merge(array, left, mid, right);
	
}





bool init()
{
	bool success = true;

	initializeRects();

	if (!font.loadFromFile("fonts/a.ttf"))
	{
		success = false;
		std::cout << "error in init function 1 \n";
	}


	return success;
}

void initializeRects()
{
	if (rects.size() != 0)
	{
		rects.clear();
	}

	srand(time(0));

	for (int i = 0; i < rectsSize; i++)
	{
		int tempHeight = (rand() % 800 + 1);
		sf::RectangleShape shape(sf::Vector2f(width, tempHeight));
		shape.setPosition(sf::Vector2f(0, windowHeight - tempHeight));
		rects.push_back(shape);
	}
}


void showText()
{

	sf::Text text = createText("Press a to QuickSort", 500, 0, 30);
	sf::Text text2 = createText("Press b to mergeSort", 500, 30, 30);
	sf::Text text3 = createText("Press r to reset the array", 500, 60, 30);
	window.draw(text3);
	window.draw(text2);
	window.draw(text);

}


sf::Text createText(std::string s , int  x , int  y , int size)
{
	sf::Text text; 
	text.setString(s);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(x,y));
	text.setCharacterSize(size);
	text.setFont(font);

	return text;

}



void renderRects()
{


	int xstart = 20;
	for (int i = 0; i < rects.size(); i++)
	{
		rects[i].setPosition(xstart, windowHeight - rects[i].getSize().y);
		window.draw(rects[i]);
		xstart += 7;

	}
}


