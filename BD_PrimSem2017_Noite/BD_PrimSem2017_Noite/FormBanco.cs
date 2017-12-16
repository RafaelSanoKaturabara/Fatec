using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace BD_PrimSem2017_Noite
{
    public partial class FormBanco : Form
    {
        /*
        public static string myConnectionString =
            "server=127.0.0.1;port=3306;uid=root;" +
            "pwd=root;database=fatec_noite";
         */
        /// <summary>
        /// String de conexão com o banco de dados
        /// </summary>
        public static string myConnectionString =
            "server=127.0.0.1;port=3306;uid=root;" +
            "pwd=1234;";
        /// <summary>
        /// Para conexão com o banco
        /// </summary>
        public static MySqlConnection conn;
        /// <summary>
        /// Comandos de acesso
        /// </summary>
        public static MySqlCommand cmd;
        /// <summary>
        /// Para acesso as linhas de uma tabela
        /// </summary>
        public static MySqlDataReader dr;
        /// <summary>
        /// Construtor
        /// </summary>
        public FormBanco()
        {
            InitializeComponent();
            try
            {
                conn = new MySqlConnection();
                conn.ConnectionString = myConnectionString;
                conn.Open();
            }
            catch (MySqlException exc)
            {
                MessageBox.Show("Falha na conexão com o banco" +
                    Environment.NewLine + exc.Message, "FATEC-Noite Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;                     // cai fora do construtor
            }
            // Criar um schema se ele não existir
            try
            {
                cmd = conn.CreateCommand();     // criar o comando
                cmd.CommandText =
                    "CREATE SCHEMA IF NOT EXISTS fatec_noite;";
                cmd.Prepare();                  // prepara o comando
                cmd.ExecuteNonQuery();          // executa o comando
            }
            catch (MySqlException exa)
            {
                MessageBox.Show("Falha na criação do schema" +
                    Environment.NewLine + exa.Message, "FATEC-Noite Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;                     // cai fora do construtor
            }
            // criar uma tabela se ela não existir
            try
            {
                cmd = conn.CreateCommand();
                cmd.CommandText =
                "CREATE TABLE IF NOT EXISTS `fatec_noite`.`clientes` (" +
                  "`cod_cliente` INT NOT NULL COMMENT 'Código do Cliente'," +
                  "`nome_cliente` VARCHAR(40) NOT NULL COMMENT 'Nome do Cliente'," +
                  "`saldo_cliente` DECIMAL(10,2) NOT NULL COMMENT 'Saldo do cliente'," +
                  "PRIMARY KEY (`cod_cliente`))" +
                "COMMENT = 'Tabela de clientes';";
                cmd.Prepare();
                cmd.ExecuteNonQuery();
            }
            catch (MySqlException exb)
            {
                MessageBox.Show("Falha na criação da tabela" +
                    Environment.NewLine + exb.Message, "FATEC-Noite Erro",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;                     // cai fora do construtor
            }
        }

        /// <summary>
        /// Quando Inserir for clicado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void inserirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // Instanciar o FormIncluir e criar o objeto myForm e se tiver que passar
            //  parâmetros para o construtor inserir no entre parentesis
            FormIncluir myForm = new FormIncluir();
            myForm.ShowDialog();
        }

        /// <summary>
        /// Quando Excluir for clicado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void excluirToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormExclusao myForm = new FormExclusao();
            myForm.ShowDialog();
        }

        /// <summary>
        /// Quando Alterar for clicado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void alterarToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormAlteracao myForm = new FormAlteracao();
            myForm.ShowDialog();
        }

        /// <summary>
        /// Quando Listagem for clicada
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void listagemToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FormListagem myForm = new FormListagem();
            myForm.ShowDialog();
        }

        /// <summary>
        /// Quando sair do programa for clicado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void sairDoProgramaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        /// <summary>
        /// Quando o formulário principal estiver sendo fechado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FormBanco_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult dlgResult =
                MessageBox.Show("Deseja sair realmente?", "FATEC-MC Pergunta",
                MessageBoxButtons.YesNo, MessageBoxIcon.Question);
            if (dlgResult == DialogResult.Yes)           // confirmou com sim?
            {
                conn.Close();                            // fecha o banco
                return;                                  // volta ao S.O.
            }
            // disse não
            e.Cancel = true;                            // cancela o evento
        }
    }
}
