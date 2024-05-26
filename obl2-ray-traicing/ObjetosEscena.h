#pragma once
class ObjetosEscena
{
	ObjetosEscena(const ObjetosEscena& obj) = delete;

	static ObjetosEscena* getInstancia() {
		static ObjetosEscena* const inst = new ObjetosEscena{};

		return inst;
	}
};

