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
    public partial class FormAlteracao : Form
    {
        private bool flgRetornar = false;           // para controle do botão retornar
        /// <summary>
        /// Strings de backup do nome e saldo
        /// </summary>
        private string szNome,                      // salva o nome na alteração
            szSaldo;                                // idem
        /// <summary>
        /// Construtor
        /// </summary>
        public FormAlteracao()
        {
            InitializeComponent();
            textBoxCodigo.Focus();
        }
        /// <summary>
        /// Quando o textbox do código for deixado
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void textBoxCodigo_Leave(object sender, EventArgs e)
        {
            int nCodigo;                                        // para conversão do código
            // se o botão retornar foi acionado
            if (flgRetornar)                                    // foi clicado o botão retornar
            {
                this.Close();                                   // fechar o form
                return;                                         // cai fora do método
            }
            try
            {
                nCodigo = Convert.ToInt32(textBoxCodigo.Text);  // validar o código
            }
            catch (Exception)
            {
                MessageBox.Show("Digite um código válido!", "FATEC-MC Alteração", 
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxCodigo.Focus();
                return;
            }
            // tentar buscar a linha da tabela deste código
            try
            {
                FormBanco.cmd = FormBanco.conn.CreateCommand();     // criar comando
                FormBanco.cmd.CommandText =
                    "SELECT * from fatec_noite.clientes WHERE cod_cliente = " +
                    textBoxCodigo.Text + ";";
                FormBanco.cmd.Prepare();                            // prepara o comando
                FormBanco.cmd.ExecuteNonQuery();    
            }
            catch (MySqlException exp)
            {
                MessageBox.Show("Cliente inexistente!" + Environment.NewLine +
                exp.Message, "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                textBoxCodigo.Focus();
                return;
            }
            // sucesso na seleção = agora ler a linha deste código
            FormBanco.dr = FormBanco.cmd.ExecuteReader();           // acessar o banco
            // verifidar se foi lido uma linha
            if (FormBanco.dr.Read())                                // tenho uma linha?
            {   // para uma linha apenas
                textBoxNome.Text =
                    FormBanco.dr.GetString("nome_cliente");         // pega o nome do cliente
                textBoxSaldo.Text =
                    Convert.ToString(FormBanco.dr.GetDecimal("saldo_cliente"));
                FormBanco.dr.Close();                               // fechar a leitura do banco
                textBoxCodigo.ReadOnly = true;                      // desabilita edição
                szNome = textBoxNome.Text;                          // salva copia do nome
                szSaldo = textBoxSaldo.Text;                        // idem saldo
            }
            else
            {   // não foi encontrada a linha
                MessageBox.Show("Código não encontrado!", "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                FormBanco.dr.Close();
                textBoxCodigo.Focus();
            }
        }

        private void buttonAlterar_Click(object sender, EventArgs e)
        {
            if (string.Compare(textBoxNome.Text, szNome) == 0 &&
                string.Compare(textBoxSaldo.Text, szSaldo) == 0)    // ambos iguais?
            {   // nenhum campo foi alterado
                MessageBox.Show("Nenhum campo foi alterado!", "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            // acertar a vírgula do saldo
            if (textBoxSaldo.Text.Contains(","))
                textBoxSaldo.Text = textBoxSaldo.Text.Replace(",", ".");
            // executar o update
            try
            {
                FormBanco.cmd = FormBanco.conn.CreateCommand();     // criar comando
                FormBanco.cmd.CommandText =
                    "UPDATE fatec_noite.clientes SET nome_cliente = \'" +
                    textBoxNome.Text + "\', saldo_cliente = " + 
                    textBoxSaldo.Text + " where cod_cliente = " +
                    textBoxCodigo.Text + ";";
                FormBanco.cmd.Prepare();                            // prepara o comando
                FormBanco.cmd.ExecuteNonQuery();
                textBoxCodigo.ReadOnly = false;                     // habilita nova atualização
                textBoxCodigo.Text = string.Empty;
                textBoxNome.Text = string.Empty;
                textBoxSaldo.Text = string.Empty;
                textBoxCodigo.Focus();
            }
            catch (MySqlException exa)
            {
                MessageBox.Show("Erro de alteração!" + Environment.NewLine + 
                exa.Message, "FATEC-MC Alteração",
                    MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
        }
        /// <summary>
        /// Foi acionado o botão retornar
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_Click(object sender, EventArgs e)
        {
            this.Close();                           // fechar o form
        }
        /// <summary>
        /// Mouse sobre o botão
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_MouseEnter(object sender, EventArgs e)
        {
            flgRetornar = true;                     // deseja retornar
            buttonRetornar.FlatStyle = FlatStyle.Flat;
        }
        /// <summary>
        /// Mouse deixou o botão
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonRetornar_MouseLeave(object sender, EventArgs e)
        {
            flgRetornar = false;                     // não deseja retornar
            buttonRetornar.FlatStyle = FlatStyle.Standard;
        }
    }
}
