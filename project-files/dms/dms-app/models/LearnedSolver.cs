﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using dms.solvers;

namespace dms.models
{
    public class LearnedSolver : Entity
    {
        private int selectionID;
        public int SelectionID
        {
            get
            {
                return selectionID;
            }

            set
            {
                selectionID = value;
            }
        }

        private int taskSolverID;
        public int TaskSolverID
        {
            get
            {
                return taskSolverID;
            }

            set
            {
                taskSolverID = value;
            }
        }

        private int learningScenarioID;
        public int LearningScenarioID
        {
            get
            {
                return learningScenarioID;
            }

            set
            {
                learningScenarioID = value;
            }
        }

        private ISolver soul;
        public ISolver Soul
        {
            get
            {
                return soul;
            }

            set
            {
                soul = value;
            }
        }

        public LearnedSolver()
        {
            this.nameTable = "LearnedSolver";
        }

        public LearnedSolver(archive.ArchiveLearnedSolver solver)
        {
            this.nameTable = "LearnedSolver";
            this.LearningScenarioID = solver.Scenario.ID;
            this.selectionID = solver.Selection.ID;
            this.taskSolverID = solver.TaskSolver.ID;
        }

        public override Dictionary<string, string> mappingTable()
        {
            Dictionary<string, string> mappingTable = new Dictionary<string, string>();
            mappingTable.Add("LearningScenarioID", "LearningScenarioID");
            mappingTable.Add("Soul", "Soul");
            mappingTable.Add("TaskSolverID", "TaskSolverID");
            mappingTable.Add("SelectionID", "SelectionID");
            base.mappingTable().ToList().ForEach(x => mappingTable.Add(x.Key, x.Value));
            return mappingTable;
        }

        public override Dictionary<string, Type> serializationParameters()
        {
            Dictionary<string, Type> serializationParameters = new Dictionary<string, Type>();
            serializationParameters.Add("Soul", typeof(ISolver));
            base.serializationParameters().ToList().ForEach(x => serializationParameters.Add(x.Key, x.Value));
            return serializationParameters;
        }

        public static List<LearnedSolver> learnedSolversOfTaskSolverID(int taskSolverID)
        {
            return LearnedSolver.where(new Query("LearnedSolver").addTypeQuery(TypeQuery.select)
                .addCondition("TaskSolverID", "=", taskSolverID.ToString()), typeof(LearnedSolver)).Cast<LearnedSolver>().ToList();
        }
    }
}
