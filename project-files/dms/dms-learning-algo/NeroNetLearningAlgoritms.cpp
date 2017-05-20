#include "NeroNetLearningAlgoritms.h"

float get_res_(void* solver, float* in)
{
	return 0;
}

int get_count_weights(void* solver)
{
	return 5;
}

float* get_weights_(void* solver)
{
	float* tmp = (float*)malloc(sizeof(float)*5);
	return tmp;
}

void set_weights_(void* solver, float* weights)
{

}

namespace dms::neroNetLearningAlgoritms
{
	float NeroNetLearningAlgoritms::startGenetic(INeuralNetwork ^ solver, array<array<float>^>^ train_x, array<float>^ train_y)
	{
		int count_person = params[0];
		void* parent_Solver;
		void** solvers = new void*[count_person];
		int a = 0;
		std::map<std::string, void*>* operations = (std::map<std::string, void*>*)solver->getOperations();
		parent_Solver = solver->getNativeSolver();

		typedef size_t(*GetWeightsCount)(void*);
		GetWeightsCount getWeightsCount = (GetWeightsCount)(*operations)["getWeightsCount"];
		size_t count_weights = getWeightsCount(parent_Solver);
		float* res_weights = new float[count_weights];

		typedef size_t(*GetAllWeights)(float*, void*);
		((GetAllWeights)((*operations)["getAllWeights"]))(res_weights, parent_Solver);

		//		(*_opers)["getAllWeights"] = nnets_perceptron::getAllWeightsPerc;

		typedef void(*SetAllWeights)(float*, void*);
		SetAllWeights set_weights = (SetAllWeights)((*operations)["setAllWeights"]);
		//		(*_opers)["setAllWeights"] = nnets_perceptron::setAllWeightsPerc;

		typedef size_t(*Solve)(float*, float*, void*);
		Solve get_res = (Solve)((*operations)["solve"]);
		//		(*_opers)["solve"] = nnets_perceptron::solvePerc;
		//		(*_opers)["getWeightsCount"] = nnets_perceptron::getWeightsCountPerc;
		typedef void*(*CopySolver)(void*);
		CopySolver copySolver = (CopySolver)((*operations)["copySolver"]);
		//		(*_opers)["copySolver"] = nnets_perceptron::copyPerc;

		typedef void(*FreeSolver)(void*&);
		FreeSolver freeSolver = (FreeSolver)((*operations)["freeSolver"]);
		//		(*_opers)["freeSolver"] = nnets_perceptron::freePerc;
		for (int i = 0; i < count_person; i++)
		{
			solvers[i] = copySolver(parent_Solver);
		}
		float** inputs = new float*[train_x->GetLength(0)];
		float* outputs = new float[train_y->Length];
		for (int i = 0; i < train_x->GetLength(0); i++)
		{
			inputs[i] = new float[train_x[i]->Length];
			for (int j = 0; j < train_x[i]->Length; j++)
			{
				inputs[i][j] = train_x[i][j];
			}
		}
		for (int i = 0; i < train_y->Length; i++)
		{
			outputs[i] = train_y[i];
		}

		int count_epochs = params[1];

		int percent_bests = params[2];

		int count_bests = (float)count_person / 100.0 * percent_bests;

		if (count_bests == 0)
		{
			count_bests = 2;
		}

		if (count_bests % 2 != 0)
		{
			if (count_person - count_bests == 0)
			{
				count_bests--;

			}
			else
			{
				count_bests++;
			}
		}

		float mutation_percent = params[3] / 100.0f;

		float res = startGeneticAlgo(solvers, inputs, outputs, train_y->Length, train_x[0]->Length,
			get_res, set_weights, count_weights, count_person, count_epochs,
			count_bests, mutation_percent, res_weights);

		set_weights(res_weights, parent_Solver);


	

		for (int i = 0; i < train_x->GetLength(0); i++)
		{
			delete[] inputs[i];
		}
		delete[] inputs;
		delete[] outputs;
		delete[] res_weights;

		for (int i = 0; i < count_person; i++)
		{
			freeSolver(solvers[i]);
		}
		delete[] solvers;

		
		solver->FetchNativeParameters();
		return res;
	}

	float NeroNetLearningAlgoritms::startBackProp(INeuralNetwork ^ solver, array<array<float>^>^ train_x, array<float>^ train_y)
	{
		void* result_Solver;
		int a = 0;
		std::map<std::string, void*>* operations = (std::map<std::string, void*>*)solver->getOperations();
		result_Solver = solver->getNativeSolver();

		typedef size_t(*Solve)(float*, float*, void*);
		Solve get_res = (Solve)((*operations)["solve"]);

		typedef size_t(*SetWeightsVector)(float*, int, void*);
		SetWeightsVector set_next_weights = (SetWeightsVector)((*operations)["setWeightsVector"]);

		float** inputs = new float*[train_x->GetLength(0)];
		float* outputs = new float[train_y->Length];

		for (int i = 0; i < train_x->GetLength(0); i++)
		{
			inputs[i] = new float[train_x[i]->Length];
			for (int j = 0; j < train_x[i]->Length; j++)
			{
				inputs[i][j] = train_x[i][j];
			}
		}

		for (int i = 0; i < train_y->Length; i++)
		{
			outputs[i] = train_y[i];
		}

	
		float res = startBackProp(result_Solver, inputs, outputs, train_y->Length, train_x[0]->Length,
			get_res, set_next_weights,

			get_next_grads,
			get_next_activate,
			count_layers, count_neuron_per_layer, count_steps,
			res_weights,
			count_lauer_to_layer, count_weights_per_lauer,
			start_lr);

		set_weights(res_weights, result_Solver);




		for (int i = 0; i < train_x->GetLength(0); i++)
		{
			delete[] inputs[i];
		}
		delete[] inputs;
		delete[] outputs;
		delete[] res_weights;

		for (int i = 0; i < count_person; i++)
		{
			freeSolver(solvers[i]);
		}
		delete[] solvers;


		solver->FetchNativeParameters();
		return res;
	}

	NeroNetLearningAlgoritms::~NeroNetLearningAlgoritms()
	{
		delete[] TeacherTypesList;
		delete[] ParamsNames;
		delete[] params;
	}

	NeroNetLearningAlgoritms::NeroNetLearningAlgoritms()
	{		
		TeacherTypesList = gcnew array<String^>(2);
		TeacherTypesList[0] = "������������ ��������";
		TeacherTypesList[1] = "�������� ��������������� ������";
		usedAlgo = TeacherTypesList[0];
		ParamsNames = gcnew array<String^>(4);
		ParamsNames[0] = "���������� ������";
		ParamsNames[1] = "���������� ����";
		ParamsNames[2] = "������� ������ ��� �����������";
		ParamsNames[3] = "����������� �������";
		params = gcnew array< float >(4);
		params[0] = 100.0f;
		params[1] = 100.0f;
		params[2] = 50.0f;
		params[3] = 0.2f;		
	}

	void NeroNetLearningAlgoritms::setUsedAlgo(System::String ^ usedAlgo_)
	{
		usedAlgo = usedAlgo_;
	}

	array<System::String^>^ NeroNetLearningAlgoritms::getTeacherTypesList()
	{
		return TeacherTypesList;
	}

	array<System::String^>^ NeroNetLearningAlgoritms::getTeacherTypesList(ISolver ^ solver)
	{
		throw gcnew System::NotImplementedException();
		// TODO: insert return statement here
	}

	array<float>^ NeroNetLearningAlgoritms::getParams()
	{
		return params;
	}

	array<System::String^>^ NeroNetLearningAlgoritms::getParamsNames()
	{
		return ParamsNames;
	}



	float NeroNetLearningAlgoritms::startLearn(ISolver^ solver, array<array<float>^>^ train_x, array<float>^ train_y)
	{
		float res = 0;

		using dms::solvers::neural_nets::kohonen::KohonenManaged;
		KohonenManaged^ kn = dynamic_cast<KohonenManaged^>(solver);
		if (kn != nullptr)
		{
			array<array<float>^>^ out = gcnew array<array<float>^>(train_y->Length);
			for (int i = 0; i < train_y->Length; i++)
			{
				out[i] = gcnew array<float>(1);
				out[i][0] = train_y[i];
			}
			kn->setClasses(out);
		}

		if (usedAlgo->Equals(TeacherTypesList[0]))
			res = startGenetic(static_cast<INeuralNetwork^>(solver), train_x, train_y);
		else
			throw gcnew System::ArgumentException("This algorithm is not supported yet", usedAlgo);
			
		return res;
	}
	

}