return {
    ["title"] = "new Tree",
    ["nodes"] = {
        [1] = {
            ["func"] = "",
            ["children"] = {
                [1] = {
                    ["children"] = {
                        [1] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_1",
                                    ["func"] = "ai_do_free_tree",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "Filter_1",
                            ["func"] = "ai_is_free",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_1",
                                    ["func"] = "ai_do_escape_tree",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "Filter_1",
                            ["func"] = "ai_is_escape",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                        [3] = {
                            ["children"] = {
                                [1] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_1",
                                    ["func"] = "ai_do_attack_tree",
                                    ["arg"] = {
                                        [1] = "",
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "Filter_1",
                            ["func"] = "ai_is_attack",
                            ["arg"] = {
                                [1] = "",
                            },
                        },
                    },
                    ["type"] = "Selector",
                    ["name"] = "Selector",
                    ["func"] = "",
                    ["arg"] = {
                        [1] = "",
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
                [1] = "",
            },
        },
    },
}