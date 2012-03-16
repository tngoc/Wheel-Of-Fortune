
#include "Quiz.h"

//test githubfdsfdsfds

Quiz::Quiz() : Sprite() {
	question = "";
	answer = "";
	number_of_words = 0;
	count_words.push_back(-1);
}

Quiz::Quiz(string pquestion,string panswer) : Sprite() {
	question = pquestion;
	answer = panswer;
	number_of_words = 0;
	count_words.push_back(-1);
}

void Quiz::addLetter(int i) {
	ostringstream ss;
	if (answer.at(i) == '\n' || answer.at(i) == '\0' || answer.at(i) == ' ' || answer.at(i) == '\r') {
		count_words.push_back(i);
		number_of_words++;
	}// lưu lại vị trí các khoảng cách, lưu cả vị trí đầu và cuối, chẳng hạn "aa" thì lưu {-1,2}
	ss << answer.at(i);

	Button* button = new Button(ss.str());
	button->setCollidable(false);
	button->setColor(D3DCOLOR_XRGB(0,255,255));
	button->setID(i);
	button->reset();
	letters.push_back(button);
}

void Quiz::arrangeLetter() {
	std::list<Button*>::iterator iter;
	letters.clear();
	int strlen = answer.length();
	if (strlen <= 0 ) return;
	for(int i = 0;i<strlen;i++) {
		addLetter(i);
	}
	number_of_words++; //do mặc định khởi tạo là 0 nên phải +1
	count_words.push_back(strlen); //lưu ký tự kết thúc
	iter = letters.begin();
}

int Quiz::inputQuiz(int x){
	HRESULT hr;
   CComPtr<IStream> pFileStream;
   CComPtr<IXmlReader> pReader;
   XmlNodeType nodeType;
   //const WCHAR* pwszPrefix;
   const WCHAR* pwszLocalName;
   const WCHAR* pwszValue;
   //UINT cwchPrefix;

   if (FAILED(hr = SHCreateStreamOnFile(L"file.xml", STGM_READ, &pFileStream))) {
      wprintf(L"Error creating file reader, error is %08.8lx", hr);
	   getchar();
      return -1;
   }

   if (FAILED(hr = CreateXmlReader(__uuidof(IXmlReader), (void**) &pReader, NULL))) {
      wprintf(L"Error creating xml reader, error is %08.8lx", hr);
      return -1;
   }

   if (FAILED(hr = pReader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit))) {
      wprintf(L"Error setting XmlReaderProperty_DtdProcessing, error is %08.8lx", hr);
      return -1;
   }

   if (FAILED(hr = pReader->SetInput(pFileStream))) {
      wprintf(L"Error setting input for reader, error is %08.8lx", hr);
      return -1;
   }

   int i = 0;
   while (S_OK == (hr = pReader->Read(&nodeType))) {
	   if (nodeType == XmlNodeType_Element) {
		   if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL))) {
            wprintf(L"Error getting local name, error is %08.8lx", hr);
            return -1;
		   }
		   if (wcscmp(pwszLocalName,L"entry") == 0) i++; // i la` so element trong xml
	   }
   }

   LARGE_INTEGER liBeggining = { 0 };
   pFileStream->Seek(liBeggining, STREAM_SEEK_SET, NULL);
   pReader->SetInput(pFileStream);

   int k=0,j=1;//k la` bien dem'. j bien' de? lay ra phan` tu? thu' j. j = 1 thi` lay' phan` tu? dau` tien
   
   while (S_OK == (hr = pReader->Read(&nodeType))) {
      switch (nodeType) {

      case XmlNodeType_Element: 
         if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL))) {
            wprintf(L"Error getting local name, error is %08.8lx", hr);
            return -1;
         }
		 if (wcscmp(pwszLocalName,L"entry") == 0) k++;

         if (FAILED(hr = pReader->MoveToElement())) {
            wprintf(L"Error moving to the element that owns the current attribute node, error is %08.8lx", hr);
            return -1;
         }
         if (pReader->IsEmptyElement() )
            wprintf(L" (empty element)\n");
         break;
      case XmlNodeType_EndElement:
          if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL))) {
            wprintf(L"Error getting local name, error is %08.8lx", hr);
            return -1;
         }
         break;

      case XmlNodeType_Text:

      case XmlNodeType_CDATA:
         if (FAILED(hr = pReader->GetValue(&pwszValue, NULL))) {
            wprintf(L"Error getting value, error is %08.8lx", hr);
            return -1;
         }
		 if (wcscmp(pwszLocalName,L"Question") == 0) {
			 setQuestion(strdup(narrow(pwszValue).c_str()));
		 }
		 else if (wcscmp(pwszLocalName,L"Answer") == 0) {
			 setAnswer(strdup(narrow(pwszValue).c_str()));
		 }
         break;

      case XmlNodeType_ProcessingInstruction:
         if (FAILED(hr = pReader->GetLocalName(&pwszLocalName, NULL))) {
            wprintf(L"Error getting name, error is %08.8lx", hr);
            return -1;
         }
         if (FAILED(hr = pReader->GetValue(&pwszValue, NULL))) {
            wprintf(L"Error getting value, error is %08.8lx", hr);
            return -1;
         }
         wprintf(L"Processing Instruction name:%S value:%S\n", pwszLocalName, pwszValue);
         break;

      case XmlNodeType_Comment:
         if (FAILED(hr = pReader->GetValue(&pwszValue, NULL))) {
            wprintf(L"Error getting value, error is %08.8lx", hr);
            return -1;
         }
         wprintf(L"Comment: %s\n", pwszValue);
         break;

      case XmlNodeType_DocumentType:
         wprintf(L"DOCTYPE is not printed\n");
         break;
      }
	  if (k > j) break;
   }
   return 0;
}

/*
chiều dài nút, chiều cao nút. x1,y1 x2,y2 là vùng mà ta muốn sắp xếp ô chữ trong đó
*/
void Quiz::setQuizPos(double width_button, double height_button, double x1, double y1, double x2, double y2) {
	double xo = x1,yo = y1,fx,fy;
	int max_words_in_row = (x2-x1)/(width_button+5);
	int max_rows = (y2-y1)/(height_button+5);
	if (letters.size() >= (max_rows*max_words_in_row)) return; //qua' dai`
	/*
	xếp từng hàng đầy nhất có thể cho đến khi không xếp dc hơn thì chuyển hàng mới tiếp tục xêp
	xếp từng hàng thì tiện căn giữa từng hàng.
	dừng khi letters.end()
	*/
	int row = 0;
	std::list<Button*>::iterator iter;
	iter = letters.begin();
	Button* button;
	int i = 0;
	button = *iter;
	fy = yo;
	i=0;
	while (iter != letters.end()) {
		int k,j;
		if (row > 0) {iter++;}
		k = count_words[i] + 1;
		for (j=i; j<=number_of_words; j++) 
			if ((count_words[j] - count_words[i]) >= max_words_in_row+2) { //gioi han max_words_in_row ky tu 1 hang`, + 2 vi` co 2 khoang trong'
				break;
			}
		i = j-1;
		fx = xo+(width_button+5)*(((max_words_in_row-(count_words[i] - k))%max_words_in_row)/2);
		while (iter != letters.end() && k < count_words[i]) {
			for (j=0;j<i;j++)
				if (k==count_words[j]) {

					goto cont;
				}
			button = *iter;
			button->setPosition(fx,fy);
			cont:
			fx = fx + width_button + 5;
			k++;
			++iter;
		}
		row++;
		fy = fy + height_button + 5;
	}
	//xong sắp xếp ô chữ, tiếp theo sẽ là tính toàn vị trí đặt ô chữ đã săp xếp trong khu vực x1,y1 x2,y2 phù hợp
	//i = row;
	double delta_y = (double)(y2-fy)/2;
	iter = letters.begin();
	while (iter != letters.end()) {
		button = *iter;
		button->setY(button->getY() + delta_y);
		++iter;
	}
}

void Quiz::drawQuiz() {
	std::list<Button*>::iterator iter;
	iter = letters.begin();
	Button* button;
	while (iter != letters.end()) {
		button = *iter;
		button->draw();
		//g_engine->addEntity(button);

		iter++;
	}
}
void Quiz::addQuizEntity() {
	std::list<Button*>::iterator iter;
	iter = letters.begin();
	Button* button;

	while (iter != letters.end()) {
		button = *iter;
		button->draw();
		iter++;
	}

	int i = 0;

}

void Quiz::reset() {
	std::list<Button*>::iterator iter;
	iter = letters.begin();

	while (iter != letters.end()) {
		delete(*iter);
		iter = letters.erase(iter);
		++iter;
	}
	letters.clear();
	number_of_words = 0;
	if (count_words.empty() == false) {
		count_words.erase(count_words.begin(),count_words.end());
		count_words.clear();
		count_words.push_back(-1);
	}
}

void Quiz::update() {
	reset();

	arrangeLetter();
	setQuizPos(27,39,this->getX(),this->getY(),this->getX() + this->getWidth(),this->getY() + this->getHeight());
	int i = this->getX();
	i = this->getY();
	i = this->getWidth();
	i = this->getHeight();
	addQuizEntity();
}



