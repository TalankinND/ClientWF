#include "ConForm.h"
#include <msclr/marshal_cppstd.h>
#include <iostream>
#include <inaddr.h>
#include <stdio.h>
#include <vector>

using namespace msclr::interop;
using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

namespace ClientWF {

    System::Void ConForm::button1_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string text1 = marshal_as<std::string>(this->textBox1->Text);
		std::string text2 = marshal_as<std::string>(this->textBox2->Text);
		std::string button_text = marshal_as<std::string>(this->button1->Text);
		std::string button_con = "Подключится";

		if (button_text == button_con) {
			
			ClientSock = gcnew Socket(AddressFamily::InterNetwork, SocketType::Stream, ProtocolType::Tcp);
			IPAddress^ ipAddr = IPAddress::Parse(this->textBox1->Text);
			IPEndPoint^ endPoint = gcnew IPEndPoint(ipAddr, stoi(text2));
			try {
				ClientSock->Connect(endPoint);
			}
			catch(SocketException^ e){
				MessageBox::Show(e->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			this->textBox1->Text = "";
			this->textBox2->Text = "";
			this->button1->Text = "Отправить";
			this->label1->Text = "Имя файла (без указания разрешения):";
			this->label2->Text = "Содержание файла:";
			this->Text = "Отправить";

		}
		else {
			array<Byte>^ msg = Encoding::ASCII->GetBytes(this->textBox1->Text);
			int bytesSent = ClientSock->Send(msg);
			if (bytesSent <= 0) {
				MessageBox::Show("Данные не были отправлены были доставлены", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			msg = Encoding::ASCII->GetBytes(this->textBox2->Text);
			bytesSent = ClientSock->Send(msg);
			if (bytesSent <= 0) {
				MessageBox::Show("Данные не были отправлены были доставлены", "Error", MessageBoxButtons::OK);
				return;
			}

			array<Byte>^ bytes = gcnew array<Byte>(1024);
			int bytesRec = ClientSock->Receive(bytes);

			MessageBox::Show(Encoding::ASCII->GetString(bytes, 0, bytesRec), "Оповещение", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
    }

	System::Void ConForm::ConForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		ClientSock->Shutdown(SocketShutdown::Both);
		ClientSock->Close();
	}
}