// Copyright (c) Microsoft Corporation
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

//
// A helper class for managing and displaying a list of data
//
#pragma once

struct ListViewConfig
{
    int MaxRows;
    int RowStartIndex;
    int RowIncrement;
    int ParentPanel;
};

template <typename ListItemType, typename ListViewRow>
class ListView
{
public:
    ListView(std::unique_ptr<ATG::UIManager> &ui, const ListViewConfig &config)
    {
        m_rows.resize(config.MaxRows);

        auto panel = ui->FindPanel<ATG::IPanel>(config.ParentPanel);

        for (int i = 0; i < config.MaxRows; ++i)
        {
            int row = config.RowStartIndex + i * config.RowIncrement;
            m_rows[i].SetControls(panel, row);
        }
    }

    void UpdateRows(const std::vector<ListItemType> &list)
    {
        for (size_t i = 0; i < m_rows.size(); ++i)
        {
            if (i >= list.size())
            {
                m_rows[i].Hide();
            }
            else
            {
                m_rows[i].Show();
                m_rows[i].Update(list[i]);
            }
        }
    }

    void SetSelectedCallback(ATG::IControl::callback_t callback)
    {
        for (auto &row : m_rows)
        {
            row.SetSelectedCallback(callback);
        }
    }

    void ClearAllRows()
    {
        for (auto &row : m_rows)
        {
            row.Hide();
        }
    }
private:
    std::vector<ListViewRow> m_rows;
};
