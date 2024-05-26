#pragma once
class ConfiguracionEscena
{
public:
	ConfiguracionEscena(const ConfiguracionEscena& obj) = delete;

	static ConfiguracionEscena* getInstancia() {
		static ConfiguracionEscena* const inst = new ConfiguracionEscena{};

		return inst;
	}
};

