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
                                    ["func"] = "setBlackboard",
                                    ["arg"] = {
                                        [1] = "runAttactFail",
                                        [2] = true,
                                    },
                                },
                            },
                            ["type"] = "Filter",
                            ["name"] = "Filter_1",
                            ["func"] = "ai_is_dis_too_long",
                            ["arg"] = {
                                [1] = 300,
                            },
                        },
                        [2] = {
                            ["children"] = {
                                [1] = {
                                    ["children"] = {
                                        [1] = {
                                            ["type"] = "Action",
                                            ["name"] = "guan qiu",
                                            ["func"] = "ai_do_skill3",
                                            ["arg"] = {
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["type"] = "Action",
                                                    ["name"] = "Action_3",
                                                    ["func"] = "ai_reset_atk_interval",
                                                    ["arg"] = {
                                                        [1] = 1,
                                                    },
                                                },
                                            },
                                            ["type"] = "Wait",
                                            ["name"] = "Wait_1",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                            },
                                        },
                                    },
                                    ["type"] = "Sequence",
                                    ["name"] = "guan qiu",
                                    ["func"] = "",
                                    ["arg"] = {
                                    },
                                },
                                [2] = {
                                    ["children"] = {
                                        [1] = {
                                            ["type"] = "Action",
                                            ["name"] = "guan qiu",
                                            ["func"] = "ai_do_skill2",
                                            ["arg"] = {
                                            },
                                        },
                                        [2] = {
                                            ["children"] = {
                                                [1] = {
                                                    ["type"] = "Action",
                                                    ["name"] = "Action_3",
                                                    ["func"] = "ai_reset_atk_interval",
                                                    ["arg"] = {
                                                        [1] = 1,
                                                    },
                                                },
                                            },
                                            ["type"] = "Wait",
                                            ["name"] = "Wait_1",
                                            ["func"] = "",
                                            ["arg"] = {
                                                [1] = 1,
                                            },
                                        },
                                    },
                                    ["type"] = "Sequence",
                                    ["name"] = "lei quan",
                                    ["func"] = "",
                                    ["arg"] = {
                                    },
                                },
                                [3] = {
                                    ["type"] = "Action",
                                    ["name"] = "Action_1",
                                    ["func"] = "setBlackboard",
                                    ["arg"] = {
                                        [1] = "runAttactFail",
                                        [2] = true,
                                    },
                                },
                            },
                            ["type"] = "RandomSelector",
                            ["name"] = "RandomSelector_1",
                            ["func"] = "",
                            ["arg"] = {
                                [1] = 1,
                                [2] = 1,
                                [3] = 1,
                            },
                        },
                    },
                    ["type"] = "Selector",
                    ["name"] = "Selector_1",
                    ["func"] = "",
                    ["arg"] = {
                    },
                },
            },
            ["type"] = "Start",
            ["name"] = "",
            ["arg"] = {
            },
        },
    },
}